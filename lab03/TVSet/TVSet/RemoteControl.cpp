#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) {
			   return TurnOn(strm);
		   } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1) },
		})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	int channelNumber;
	args >> channelNumber;
	if (!m_tv.IsTurnedOn())
	{
		m_output << "Can't select channel because TV is turned off\n";
	}
	else
	{
		if (m_tv.SelectChannel(channelNumber))
		{
			m_output << "TV channel changed to " << channelNumber << endl;
		}
		else
		{
			m_output << "Invalid channel\n";
		}
	}
	return true;
}

bool CRemoteControl::SelectPreviousChannel(istream&)
{
	m_tv.SelectPreviousChannel();
	string info = (m_tv.IsTurnedOn())
		? ("TV channel changed to " + to_string(m_tv.GetChannel()) + "\n")
		: "Can't select previous channel because TV is turned off\n";

	m_output << info;

	return true;
}


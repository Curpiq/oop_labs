#pragma once

class CTVSet
{
public:
	int GetChannel()const;
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	bool SelectPreviousChannel();
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;
};

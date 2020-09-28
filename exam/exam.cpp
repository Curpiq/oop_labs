// exam.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

class CTime
{
private:
	int m_hours;
	int m_minutes;
	int m_seconds;
public:
	// Конструирует время (чч:мм:сс). 
	// Если часы, минуты, или секунды выходят за пределы 23:59:59, бросает
	// исключение invalid_argument
	CTime(int hours, int minutes, int seconds)
	{
		if (hours > 23 || minutes > 59 || seconds > 59 || hours < 0 || minutes < 0 || seconds < 0)
		{
			throw invalid_argument("");
		}
		m_hours = hours;
		m_minutes = minutes;
		m_seconds = seconds;
	}

	// Возвращает количество часов (0..23)
	int GetHours()const
	{
		return m_hours;
	}

	// Возвращает количество минут (0..59)
	int GetMinutes()const
	{
		return m_minutes;
	}

	// Возвращает количество секунд (0..59)
	int GetSeconds()const
	{
		return m_seconds;
	}

	// Возвращает строковое представление времени в формате чч:мм:сс
	string ToString()const
	{
		string hours = (m_hours < 10) ? "0" + to_string(m_hours) : to_string(m_hours);
		string minutes = (m_minutes < 10) ? "0" + to_string(m_minutes) : to_string(m_minutes);
		string seconds = (m_seconds < 10) ? "0" + to_string(m_seconds) : to_string(m_seconds);
		return hours + ":" + minutes + ":" + seconds;
	}
	CTime operator +(const CTime& time) const;
	CTime operator -(const CTime& time) const;
	CTime& operator +=(const CTime& time);
	CTime& operator -=(const CTime& time);
};
ostream& operator <<(ostream& stream, const CTime& time)
{
	stream << time.ToString();
	return stream;
}
/*
Реализовать методы класса и перечисленные ниже операции. Сложение и вычитание выполняется в пределах суток
Примеры:
	+	складывает временные интервалы: 23:59:17 + 01:12:13 -> 01:11:30
	-	вычитает временные интервалы: 00:15:25 - 01:16:25 -> 22:59:00
	+=	a += b аналогично a = a + b
	-=	a -= b аналогично a = a - b
	<<	выводит время в заданный ostream в формает чч:мм:сс
*/

CTime CTime::operator+(const CTime& time) const
{
	return CTime(m_hours + time.GetHours(), m_minutes + time.GetMinutes(), m_seconds + time.GetSeconds());
}

CTime CTime::operator-(const CTime& time) const
{
	return CTime(m_hours - time.GetHours(), m_minutes - time.GetMinutes(), m_seconds + time.GetSeconds());
}

CTime& CTime::operator+=(const CTime& time)
{
	*this = *this + time;
	return *this;
}

CTime& CTime::operator-=(const CTime& time)
{
	*this = *this - time;
	return *this;
}

int main()
{
	CTime time1(01, 15, 25);
	cout << time1 << endl;

	CTime time2(01, 16, 25);

	cout << time1 + time2 << endl;
}

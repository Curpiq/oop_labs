#include "stdafx.h"
#include "../TVSet/TVSet.h"

struct TVSetFixture
{
	CTVSet tv;
};

BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	// не может переключать канал в выключенном состо€нии
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}


	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};

	// после включени€
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
	// отображает канал 1
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		// можно выключить
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}
		// позвол€ет выбрать канал от 1 до 99
		BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
		{
			BOOST_CHECK(tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			// ¬ыбираем канал между 1 и 99
			BOOST_CHECK(tv.SelectChannel(42));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			// ѕри попытке выбрать канал за пределами [1; 99] 
			// телевизор не должен мен€ть свой канал
			BOOST_CHECK(!tv.SelectChannel(0));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);
		}

		BOOST_AUTO_TEST_CASE(can_select_previous_channel)
		{
			tv.SelectChannel(2);
			tv.SelectChannel(99);
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 2);
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			//Ќе переключает канал, если телевизор выключен
			tv.TurnOff();
			BOOST_CHECK(!tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_ : when_turned_on_
	{
		after_subsequent_turning_on_()
		{
			tv.SelectChannel(33);
			tv.TurnOff();
			tv.TurnOn();
		}
	};

	// после повторного включени€
	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		// восстанавливает последний выбранный канал
		BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
	    {
		    BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
	    }
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()



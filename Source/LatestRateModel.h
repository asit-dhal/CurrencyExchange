/*
  ==============================================================================

    LatestRateModel.h
    Created: 19 Feb 2019 11:55:40pm
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Rate.h"
#include "JsonRequest.h"

class LatestRateModel :
	public Thread::Listener,
	public AsyncUpdater
{
public:
	class Listener
	{
	public:
		virtual ~Listener() = default;
		virtual void modelUpdated() = 0;
	};

	void exitSignalSent() override;
	void handleAsyncUpdate() override;
	void addListener(Listener* listener);
	Currency getBaseCurrency() const;
	std::vector<std::pair<Currency, double>> getCurrencySpotPrices() const;
	Time getTimeOfLastUpdate() const;
	void refresh();

private:
	LatestRateModel();
	void informListener();
	void parseResponse(String response);

private:
	std::vector<std::pair<Currency, double>> m_currencySpotPrices;
	Currency m_baseCurrency;
	Time m_time;
	JsonRequest m_req;
	std::vector<Listener*> m_listeners;

public:
	JUCE_DECLARE_SINGLETON(LatestRateModel, false);
};
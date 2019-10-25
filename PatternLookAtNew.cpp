#include <iostream> // observer pattern
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class IObserver
{
public:
	virtual void update(int t) = 0;
	virtual void showData() = 0;

};


class ISubject
{
public:
	virtual void addObserver(IObserver * pObj) = 0;
	virtual void removeObserver(IObserver * pObj) = 0;
	virtual void updateObserver() = 0;

};


class TempSensor :public ISubject
{
private:
	list<IObserver *>observers;

public:
	int getTempSensor()
	{
		return 100 + rand() % 25 - 50;
	}

	void addObserver(IObserver * pObj)
	{
		observers.push_back(pObj);
	}

	void removeObserver(IObserver * pObj)
	{
		observers.remove(pObj);
	}

	void updateObserver()
	{
		int currentTemp = this->getTempSensor();
		for (auto obj : observers)
		{
			obj->update(currentTemp);
		}
	}

};


class TempHistoryCollector :public IObserver
{
private:
	vector<int>tempperature;

public:
	void update(int _tempperature)
	{
		tempperature.push_back(_tempperature);
	}

	void showData()
	{
		for (auto t : tempperature)
		{
			cout << t << " ";
		}
		cout << endl;
	}
};


class TempMinMaxCollector :public IObserver
{
private:
	int maxTemp = 0;
	int minTemp = 999;

public:
	void update(int _tempperature)
	{
		maxTemp = max(maxTemp, _tempperature);
		minTemp = min(minTemp, _tempperature);
	}

	void showData()
	{
		cout << "Min : " << minTemp << "\nMax : "
			 << maxTemp << endl;
	}
};


int main()
{
	ISubject * ts = new TempSensor;
	TempHistoryCollector * hc = new TempHistoryCollector;
	TempMinMaxCollector * tmmc = new TempMinMaxCollector;

	ts->addObserver(hc);
	ts->addObserver(tmmc);

	for (int i = 0; i < 5; i++)
	{
		ts->updateObserver();
	}

	hc->showData();
	tmmc->showData();
}
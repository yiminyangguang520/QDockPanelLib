#pragma once

#include <QWidget>
#include <QByteArray>

class QDockDataBuilder
{
public:
	QDockDataBuilder(void);
	~QDockDataBuilder(void);

	QByteArray toByteArray();
	bool fromByteArray(const QByteArray& ba);
	void setWidget(QWidget* widget)
	{
		data_.widget = widget;
	}
	QWidget* getWidget(){return data_.widget;}
private:
	struct 
	{
		QWidget* widget;
	} data_;
};


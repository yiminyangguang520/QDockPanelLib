#include "QDockDataBuilder.h"
#include <memory>

QDockDataBuilder::QDockDataBuilder(void)
{
}

QDockDataBuilder::~QDockDataBuilder(void)
{
}

QByteArray QDockDataBuilder::toByteArray()
{
	QByteArray ba(sizeof(data_),'\0');
	std::memcpy(ba.data(),&data_,sizeof(data_));
	return ba;
}

bool QDockDataBuilder::fromByteArray( const QByteArray& ba )
{
	if (ba.size() != sizeof(data_))
	{
		return false;
	}

	std::memcpy(&data_,ba.data(),sizeof(data_));
	return true;
}

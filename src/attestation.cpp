#include "attestation.h"

Attestation::Attestation(QObject *parent) : QObject(parent)
{

}

QString Attestation::name() const
{
	return name_;
}

void Attestation::setName(QString name)
{
	if (name_ == name)
		return;

	name_ = name;
	emit nameChanged(name_);
}

#include "attestationmanager.h"

#include <QDirIterator>
#include <QStandardPaths>
#include <QProcess>

AttestationManager::AttestationManager(QObject *parent) : QObject(parent)
{
	refresh_();
}

QVariantList AttestationManager::attestations() const
{
	return attestations_;
}

void AttestationManager::openAttestation(QString attestation)
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");
	auto file = dir.absolutePath() + "/" + attestation;
	QProcess::startDetached("xdg-open", QStringList{file});
}

void AttestationManager::deleteAttestation(QString attestation)
{
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");
	dir.remove(attestation);
	refresh_();
}

void AttestationManager::setAttestations(QVariantList attestations)
{
	if (attestations_ == attestations)
		return;

	attestations_ = attestations;
	emit attestationsChanged(attestations_);
}

void AttestationManager::refresh_()
{
	attestations_.clear();
	auto base = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
	auto dest = base.at(0);
	QDir dir(dest);
	dir.cd("Attestations");

	QDirIterator it(dir.absolutePath(), QDir::Files, QDirIterator::NoIteratorFlags);
	while (it.hasNext())
	{
		auto str = it.next();
		attestations_.push_back(it.fileName());
	}
	emit attestationsChanged(attestations_);
}

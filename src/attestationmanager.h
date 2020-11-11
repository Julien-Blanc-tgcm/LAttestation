#ifndef ATTESTATIONMANAGER_H
#define ATTESTATIONMANAGER_H

#include <QObject>
#include <QVariantList>

class AttestationManager : public QObject
{
	Q_OBJECT
	QStringList attestations_;

  public:
	explicit AttestationManager(QObject* parent = nullptr);

	Q_PROPERTY(QStringList attestations READ attestations WRITE setAttestations NOTIFY attestationsChanged)

	QStringList attestations() const;

	Q_INVOKABLE void openAttestation(QString attestation);

	Q_INVOKABLE void deleteAttestation(QString attestation);

  signals:

	void attestationsChanged(QStringList attestations);

  public slots:
	void setAttestations(QStringList attestations);

  private:
	void refresh_();
};

#endif // ATTESTATIONMANAGER_H

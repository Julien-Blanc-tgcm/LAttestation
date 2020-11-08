#ifndef ATTESTATIONMANAGER_H
#define ATTESTATIONMANAGER_H

#include <QObject>
#include <QVariantList>

class AttestationManager : public QObject
{
	Q_OBJECT
	QVariantList attestations_;

  public:
	explicit AttestationManager(QObject* parent = nullptr);

	Q_PROPERTY(QVariantList attestations READ attestations WRITE setAttestations NOTIFY attestationsChanged)

	QVariantList attestations() const;

	Q_INVOKABLE void openAttestation(QString attestation);

	Q_INVOKABLE void deleteAttestation(QString attestation);

  signals:

	void attestationsChanged(QVariantList attestations);

  public slots:
	void setAttestations(QVariantList attestations);

  private:
	void refresh_();
};

#endif // ATTESTATIONMANAGER_H

#ifndef GENERATORIMAGEPROVIDER_H
#define GENERATORIMAGEPROVIDER_H

#include "generator.h"

#include <QQuickImageProvider>

class GeneratorImageProvider : public QQuickImageProvider
{
  public:
	explicit GeneratorImageProvider(Generator* generator);

  private:
	Generator* generator_;

	// QQuickImageProvider interface
public:
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // GENERATORIMAGEPROVIDER_H

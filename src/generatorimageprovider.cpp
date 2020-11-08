#include "generatorimageprovider.h"

#include <QDebug>

GeneratorImageProvider::GeneratorImageProvider(Generator* generator) :
    QQuickImageProvider(ImageType::Image), generator_{generator}
{

}

QImage GeneratorImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
	qDebug() << "Requesting image " << id;
	if (id.startsWith("image2d"))
	{
		auto ret = generator_->bitmap2d();
		*size = ret.size();
		if (requestedSize.isValid())
			return ret.scaled(requestedSize, Qt::AspectRatioMode::KeepAspectRatio);
		else
			return ret;
	}
	if (id.startsWith("imagePdf"))
	{
		auto ret = generator_->bitmapPdf();
		*size = ret.size();
		if (requestedSize.isValid())
			return ret.scaled(requestedSize, Qt::AspectRatioMode::KeepAspectRatio);
		else
		{
			return ret;
		}
	}
	return QImage{};
}

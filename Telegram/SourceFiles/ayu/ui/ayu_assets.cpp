// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2023

#include "ayu_assets.h"
#include "ayu/ayu_settings.h"

static QString LAST_LOADED_NAME;

static QImage LAST_LOADED;

static QImage LAST_LOADED_NO_MARGIN;

void loadAppIco()
{
	auto settings = &AyuSettings::getInstance();

	QString appDataPath = QDir::fromNativeSeparators(qgetenv("APPDATA"));
	QString tempIconPath = appDataPath + "/AyuGram.ico";

	// workaround for read-only file
	auto f = QFile(tempIconPath);
	if (f.exists()) {
		f.setPermissions(QFile::WriteOther);
		f.remove();
	}
	f.close();
	QFile::copy(qsl(":/gui/art/ayu/%1/logo256_no_margin.ico").arg(settings->appIcon), tempIconPath);
}

void loadIcons()
{
	auto settings = &AyuSettings::getInstance();
	if (LAST_LOADED_NAME != settings->appIcon) {
		LAST_LOADED_NAME = settings->appIcon;

		LAST_LOADED = QImage(qsl(":/gui/art/ayu/%1/logo256.png").arg(settings->appIcon));
		LAST_LOADED_NO_MARGIN = QImage(qsl(":/gui/art/ayu/%1/logo256_no_margin.png").arg(settings->appIcon));
	}
}

QImage logoPreview()
{
	return QImage(qsl(":/gui/art/ayu/default/logo256.png"));
}

QImage logoAltPreview()
{
	return QImage(qsl(":/gui/art/ayu/alt/logo256.png"));
}

QImage logoNothingPreview()
{
	return QImage(qsl(":/gui/art/ayu/nothing/logo256.png"));
}

QString currentAppLogoName()
{
	return LAST_LOADED_NAME;
}

QImage currentAppLogo()
{
	loadIcons();
	return LAST_LOADED;
}

QImage currentAppLogoNoMargin()
{
	loadIcons();
	return LAST_LOADED_NO_MARGIN;
}

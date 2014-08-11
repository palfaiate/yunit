/*
 * Copyright (C) 2013-2014 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlComponent>

class QQuickItem;
class MirSurfaceItem;

// unity-api
#include <unity/shell/application/ApplicationInfoInterface.h>

using namespace unity::shell::application;

class ApplicationInfo : public ApplicationInfoInterface {
    Q_OBJECT

    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)
    Q_PROPERTY(MirSurfaceItem* surface READ surface NOTIFY surfaceChanged)
    Q_PROPERTY(QQmlListProperty<MirSurfaceItem> promptSurfaces READ promptSurfaces NOTIFY promptSurfacesChanged DESIGNABLE false)

    // Only exists in this fake implementation

public:
    ApplicationInfo(QObject *parent = NULL);
    ApplicationInfo(const QString &appId, QObject *parent = NULL);
    ~ApplicationInfo();

    Q_INVOKABLE void updateScreenshot() override;
    Q_INVOKABLE void discardScreenshot() override;

    void setIconId(const QString &iconId);
    void setScreenshotId(const QString &screenshotId);

    void setAppId(const QString &value) { m_appId = value; }
    QString appId() const override { return m_appId; }

    void setName(const QString &value);
    QString name() const override { return m_name; }

    QString comment() const override { return QString(); }

    QUrl icon() const override { return m_icon; }

    void setStage(Stage value);
    Stage stage() const override { return m_stage; }

    Q_INVOKABLE void setState(State value);
    State state() const override { return m_state; }

    void setFocused(bool value);
    bool focused() const override { return m_focused; }

    QUrl screenshot() const override { return m_screenshot; }

    void setFullscreen(bool value);
    bool fullscreen() const { return m_fullscreen; }

    void setSurface(MirSurfaceItem* surface);
    MirSurfaceItem* surface() const { return m_surface; }

    void removeSurface(MirSurfaceItem* surface);

    void addPromptSurface(MirSurfaceItem* surface);
    QList<MirSurfaceItem*> promptSurfaceList() const;
    QQmlListProperty<MirSurfaceItem> promptSurfaces();

Q_SIGNALS:
    void surfaceChanged(MirSurfaceItem*);
    void promptSurfacesChanged();
    void fullscreenChanged(bool value);

private Q_SLOTS:
    void createSurface();

private:
    static int promptSurfaceCount(QQmlListProperty<MirSurfaceItem> *prop);
    static MirSurfaceItem* promptSurfaceAt(QQmlListProperty<MirSurfaceItem> *prop, int index);
    void setIcon(const QUrl &value);
    void setScreenshot(const QUrl &value);

    QUrl m_screenshotUrl;

    QString m_appId;
    QString m_name;
    QUrl m_icon;
    Stage m_stage;
    State m_state;
    bool m_focused;
    QUrl m_screenshot;
    bool m_fullscreen;
    MirSurfaceItem* m_surface;

    QQuickItem *m_parentItem;
    QList<MirSurfaceItem*> m_promptSurfaces;
};

Q_DECLARE_METATYPE(ApplicationInfo*)
Q_DECLARE_METATYPE(QQmlListProperty<MirSurfaceItem>)

#endif  // APPLICATION_H

/*
 * This file is part of EasyRPG Editor.
 *
 * EasyRPG Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Editor. If not, see <http://www.gnu.org/licenses/>.
 */

#include "faceset_painted_item.h"
#include "core.h"
#include "common/image_loader.h"
#include "common/dbstring.h"
#include "model/project_data.h"

#include <lcf/rpg/actor.h>

FaceSetPaintedItem::FaceSetPaintedItem(QQuickItem* parent) :
	QQuickPaintedItem(parent) {
	m_image = QPixmap(48, 48);
	m_image.fill(QColor(255, 255, 255, 0));
}

void FaceSetPaintedItem::setProject(ProjectBinding* newProject) {
	if (m_project == newProject)
		return;
	m_project = newProject;
	m_need_refresh = true;
	update();
	emit projectChanged();
}

void FaceSetPaintedItem::setName(const QString& newName) {
	if (m_name == newName)
		return;
	m_name = newName;
	m_need_refresh = true;
	update();
	emit nameChanged();
}

void FaceSetPaintedItem::setIndex(int newIndex) {
	if (m_index == newIndex)
		return;
	m_index = newIndex;
	update();
	emit indexChanged();
}

QRect FaceSetPaintedItem::faceRect() const {
	return {
			(m_index % 4) * 48,
			m_index / 4 * 48,
			48,
			48
	};
}

QRectF FaceSetPaintedItem::boundingRect() const {
	return {0., 0., 48., 48.};
}

void FaceSetPaintedItem::paint(QPainter* painter) {
	if (!m_project) {
		return;
	}

	refresh();
	painter->drawPixmap(boundingRect(), m_image, faceRect());
}

void FaceSetPaintedItem::refresh() {
	if (!m_need_refresh) {
		return;
	}

	QString path = m_project->projectData().project().findFile(FACESET, m_name, FileFinder::FileType::Image);
	if (!path.isEmpty()) {
		m_image = ImageLoader::Load(path);
	} else {
		m_image = QPixmap(48, 48);
		m_image.fill(QColor(255, 255, 255, 0));
	}

	m_need_refresh = false;
}

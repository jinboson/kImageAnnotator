/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "IconCreater.h"

IconCreater::IconCreater(QSize iconSize)
{
    setIconSize(iconSize);
}

QSize IconCreater::iconSize() const
{
    return mIconSize;
}

void IconCreater::setIconSize(const QSize& iconSize)
{
    mIconSize = iconSize;
}

QIcon IconCreater::createColorIcon(const QColor& color) const
{
    QPixmap pixmap(mIconSize);
    pixmap.fill(color);
    QPainter painter(&pixmap);
    auto penWidth = painter.pen().width();
    painter.setPen(QColor(Qt::gray));
    painter.drawRect(0,0, mIconSize.width() - penWidth, mIconSize.height() - penWidth);

    return QIcon(pixmap);
}

QIcon IconCreater::createSizeIcon(int size) const
{
    auto icon = QIcon::fromTheme(QStringLiteral("format-align-vertical-center"));
    
    QPixmap pixmap(mIconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor(QColor(Qt::black));
    pen.setWidth(size);
    painter.setPen(pen);
    painter.drawPixmap(QPointF(0,0), icon.pixmap(QSize(15, 15)));
    painter.drawLine(QPointF(17, mIconSize.height() / 2), QPointF(mIconSize.width(), mIconSize.height() / 2));

    return QIcon(pixmap);
}
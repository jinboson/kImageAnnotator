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

#include "ToolPicker.h"

ToolPicker::ToolPicker()
{
    initGui();

    connect(mButtonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &ToolPicker::buttonClicked);
}

ToolPicker::~ToolPicker()
{
    delete mButtonGroup;
    delete mLayout;
}

void ToolPicker::setTool(ToolTypes newTool)
{
    auto selectedAction = mButtonToTool.key(newTool);
    selectedAction->setChecked(true);
    setToolAndNotify(newTool);
}

ToolTypes ToolPicker::tool()
{
    return mSelectedToolType;
}

void ToolPicker::initGui()
{
    mLayout = new QGridLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mButtonGroup = new QButtonGroup(this);

    auto button = createButton(i18n("Select"), QPixmap(QStringLiteral(":/icons/select")));
    mButtonToTool[button] = ToolTypes::Select;
    mLayout->addWidget(button, 0, 0);
    mButtonGroup->addButton(button);

    button = createButton(i18n("Line"), QPixmap(QStringLiteral(":/icons/line")));
    mButtonToTool[button] = ToolTypes::Line;
    mLayout->addWidget(button, 0, 1);
    mButtonGroup->addButton(button);

    button = createButton(i18n("Rect"), QPixmap(QStringLiteral(":/icons/rect")));
    mButtonToTool[button] = ToolTypes::Rect;
    mLayout->addWidget(button, 2, 0);
    mButtonGroup->addButton(button);

    button = createButton(i18n("Ellipse"), QPixmap(QStringLiteral(":/icons/ellipse")));
    mButtonToTool[button] = ToolTypes::Ellipse;
    mLayout->addWidget(button, 2, 1);
    mButtonGroup->addButton(button);

    button = createButton(i18n("Arrow"), QPixmap(QStringLiteral(":/icons/arrow")));
    mButtonToTool[button] = ToolTypes::Arrow;
    mLayout->addWidget(button, 3, 0);
    mButtonGroup->addButton(button);

    button = createButton(i18n("Number"), QPixmap(QStringLiteral(":/icons/number")));
    mButtonToTool[button] = ToolTypes::Number;
    mLayout->addWidget(button, 3, 1);
    mButtonGroup->addButton(button);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

QToolButton* ToolPicker::createButton(const QString& tooltip, const QPixmap& pixmap)
{
    auto button = new QToolButton(this);
    button->setCheckable(true);
    button->setAutoRaise(true);
    button->setIconSize(QSize(24, 24));
    button->setIcon(pixmap);
    button->setToolTip(tooltip);
    button->setFocusPolicy(Qt::NoFocus);
    return button;
}

void ToolPicker::buttonClicked(QAbstractButton* button)
{
    setToolAndNotify(mButtonToTool.value(button));
}

void ToolPicker::setToolAndNotify(ToolTypes newTool)
{
    mSelectedToolType = newTool;
    emit toolSelected(mSelectedToolType);
}

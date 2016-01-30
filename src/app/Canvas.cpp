/* Copyright (c) 2014-2015 "Omnidome" by cr8tr
 * Dome Mapping Projection Software (http://omnido.me).
 * Omnidome was created by Michael Winkelmann aka Wilston Oreo (@WilstonOreo)
 *
 * This file is part of Omnidome.
 *
 * Omnidome is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Canvas.h"

#include "ui_omni_ui_Canvas.h"

#include <QVBoxLayout>
#include <QVariant>

#include <omni/Session.h>
#include <omni/canvas/Interface.h>

namespace omni {
    namespace ui {
        Canvas::Canvas(QWidget *_parent) :
            CollapsibleGroupBox(_parent),
            ui_(new Ui::Canvas)
        {
            setTitle("Canvas");
            ui_->setupUi(widget());

            // Add canvas types from Factory
            for (auto& _idCanvasClass : omni::canvas::Factory::classes())
            {
                QString _id = _idCanvasClass.first.str();
                ui_->boxCanvasSelect->addItem(QIcon(QString(":/canvas/") + _id +
                                                    QString(
                                                        ".png")), _id,
                                              QVariant(_id));
            }

            // Configure layout
            /*
            QLayout *_layout = new QVBoxLayout;
            _layout->setSpacing(2);
            _layout->setContentsMargins(0, 0, 0, 0);
            ui_->widget->setLayout(_layout);

            // Update parameter when canvas has changed
            connect(ui_->widget, SIGNAL(parametersUpdated()), this,
                    SIGNAL(canvasChanged()));

            connect(ui_->boxCanvasSelect, SIGNAL(currentIndexChanged(QString)), this,
                    SLOT(canvasTypeSelected(QString)));

            connect(ui_->chkDisplayInput, SIGNAL(clicked(bool)),this,
                    SIGNAL(displayInputToggled(bool)));

            connect(ui_->boxProjectorViewMode, SIGNAL(currentIndexChanged(int)),this,
                    SLOT(changeProjectorViewMode(int)));
            */
        }

        Canvas::~Canvas()
        {}

        void Canvas::changeProjectorViewMode(int _index) {
            emit projectorViewModeChanged(ProjectorViewMode(_index));
        }

        void Canvas::sessionParameters()
        {
            if (!session()->canvas())
            {
                session()->setCanvas("Box");
                emit canvasTypeChanged();
            }

            // Search combobox for available canvas types
            int _index = 0;

            for (int i = 0; i < ui_->boxCanvasSelect->count(); ++i)
            {
                QString _id = ui_->boxCanvasSelect->itemData(i).toString();

                if (_id == session()->canvas()->getTypeId().str())
                {
                    _index = i;
                }
            }

            ui_->boxCanvasSelect->setCurrentIndex(_index);
            //ui_->widget->setCanvas(session()->canvas());
            emit canvasChanged();
        }

        void Canvas::canvasTypeSelected(QString _id)
        {
            if (!session() || this->isLocked()) return;

            session()->setCanvas(_id);

            //if (session()->canvas()) ui_->widget->setCanvas(session()->canvas());

            emit canvasTypeChanged();
        }
    }
}

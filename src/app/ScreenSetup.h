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

#ifndef OMNI_UI_SCREENSETUP_H_
#define OMNI_UI_SCREENSETUP_H_

#include <list>
#include <QWidget>

#include <omni/proj/ScreenSetup.h>
#include <omni/ui/mixin/TransformedRect.h>
#include <omni/ui/mixin/DataModel.h>
#include "proj/Tuning.h"
#include "ScreenItem.h"

namespace omni {
  class Session;

  namespace ui {
    namespace proj {
      class TuningList;
    }

    /**@brief A widget for seting up fullscreen windows
     * @details Holds fullscreen widgets
     **/
    class ScreenSetup :
      public QWidget,
      public mixin::SharedDataModel<Session>,
      public mixin::TransformedRect<ScreenSetup>{
        Q_OBJECT
        OMNI_UI_SHARED_DATAMODEL(Session)

      public:
        ScreenSetup(QWidget * = nullptr);
        ~ScreenSetup();

        inline QRect desktopRect() const {
          return omni::proj::ScreenSetup::desktopRect();
        }

        void setTuningList(proj::TuningList*);
        proj::TuningList* tuningList();
        proj::TuningList const* tuningList() const;

      public slots:
        /// Update screen dimensions
        void updateScreens();

        /// Update all fullscreen views
        void updateViews();

        void closeFullscreenWindows();

        void assignNewTuningToNextFreeScreen();

      signals:
        void dataModelChanged();

      protected:
        void paintEvent(QPaintEvent *);

        void mouseMoveEvent(QMouseEvent *);

        /// Detach tuning on double click on screen event
        void mouseDoubleClickEvent(QMouseEvent *);
        void dragEnterEvent(QDragEnterEvent *);
        void dragMoveEvent(QDragMoveEvent *);
        void dropEvent(QDropEvent *);

      private:
        friend ScreenItem;
        friend SubScreenItem;

        /// Set session parameters
        void dataToFrontend();

        bool frontendToData() {
          return false;
        }

        void assignTuning(omni::proj::Tuning*);

        /**@brief Returns pointer to a SubScreenItem under given position
         *@detail Returns null otherwise
         **/
        SubScreenItem* getSubScreenItemAtPos(QPoint const&);

        std::map<QScreen const *, std::unique_ptr<ScreenItem> > screenItems_;
        SubScreenItem* currentSubScreenItem_ = nullptr;
        proj::TuningList* tuningList_ = nullptr;
    };
  }
}

#endif /* OMNI_UI_SCREENSETUP_H_ */

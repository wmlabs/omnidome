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

#ifndef OMNI_CANVAS_BOX_H_
#define OMNI_CANVAS_BOX_H_

#include <QObject>
#include <QtPlugin>
#include <omni/canvas/Envelope.h>
#include <omni/visual/Box.h>

namespace omni
{
  namespace canvas
  {
    /**@brief A box-shaped canvas.
      *@detail Can be used for rooms or boxes
     **/
    class Box : public QObject, public Envelope
    {
        OMNI_CANVAS_PLUGIN_DECL
    public:
      OMNI_REGISTER_CLASS(Factory,Box)

      /// Default constructor
      Box();

      /// Destructor
      ~Box();

      /// Draw box
      void draw() const;

      /// Generate box vertices
      void update();

      /// Return size of the box
      QVector3D size() const;

      /// Center is on the center of the bottom of the box
      QVector3D center() const;

      /// Return set center of sphere
      void setCenter(QVector3D const&);


      /// Set size of the box
      void setSize(QVector3D const&);

      /// Deserialize from stream
      void fromStream(QDataStream&);

      /// Serialize to stream
      void toStream(QDataStream&) const;

      /// Make new box parameter widget
      QWidget* widget();

      QMatrix4x4 matrix() const;

      EulerAngles& angles();
      EulerAngles const& angles() const;

    private:
      visual::Box vizBox_;
      QVector3D center_;
      EulerAngles angles_;
    };
  }
}

#endif /* OMNI_CANVAS_BOX_H_ */

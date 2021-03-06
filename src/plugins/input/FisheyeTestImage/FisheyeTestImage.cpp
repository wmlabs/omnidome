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

#include "FisheyeTestImage.h"

#include <omni/util.h>
#include <omni/visual/Shader.h>
#include <omni/ui/TestInputPreview.h>

namespace omni
{
  namespace input
  {
    FisheyeTestImage::FisheyeTestImage(Interface const* _parent) :
      TestImage(_parent)
    {
    }

    FisheyeTestImage::~FisheyeTestImage()
    {
    }

    QString FisheyeTestImage::fragmentShaderSource() const
    {
      static QString _fragmentSrc;
      if (_fragmentSrc.isEmpty())
        _fragmentSrc = visual::ShaderCompiler::compile(":/shaders/FisheyeTestImage.frag");
      return _fragmentSrc;
    }

    QString FisheyeTestImage::vertexShaderSource() const
    {
      static QString _vertSrc;
      if (_vertSrc.isEmpty())
        _vertSrc = visual::ShaderCompiler::compile(":/shaders/test_image.vert");
      return _vertSrc;
    }

    QSize FisheyeTestImage::size() const
    {
      return QSize(2048,2048);
    }

    QWidget* FisheyeTestImage::widget() {
        return new ui::TestInputPreview(this);
    }
  }
}

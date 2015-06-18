#ifndef OMNI_INPUT_IMAGE_H_
#define OMNI_INPUT_IMAGE_H_

#include "Interface.h"

namespace omni
{
  namespace input
  {
    class Image : public Interface
    {
    public:
      OMNI_TYPEID("Image")

      Image();
      Image(QString const& _path);

      ~Image();

      void bind();
      void release();
      void free();
      void update();

      GLuint textureId() const;

      void load(QString const& _path);
      void reload();
      QString path() const;
     
      void toStream(QDataStream&) const;
      void fromStream(QDataStream&);

    private:
      QImage image_;
      std::unique_ptr<QOpenGLTexture> texture_;
      QString path_;
    };
  }
}

#endif /* OMNI_INPUT_IMAGE_H_ */

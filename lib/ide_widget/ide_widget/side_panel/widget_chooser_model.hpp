#ifndef IDE_WIDGET_CHOOSER_MODEL_HPP
#define IDE_WIDGET_CHOOSER_MODEL_HPP

#include "../api.hpp"
#include <QObject>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT WidgetChooserModel : public QObject
{
  Q_OBJECT
public:
  explicit WidgetChooserModel(QObject *parent = NULL);

};

} // namespace IDE

#endif // IDE_WIDGET_CHOOSER_MODEL_HPP

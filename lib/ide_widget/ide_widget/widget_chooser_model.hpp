#ifndef IDE_WIDGET_CHOOSER_MODEL_HPP
#define IDE_WIDGET_CHOOSER_MODEL_HPP

#include <QObject>

namespace IDE
{

class WidgetChooserModel : public QObject
{
  Q_OBJECT
public:
  explicit WidgetChooserModel(QObject *parent = NULL);

};

} // namespace IDE

#endif // IDE_WIDGET_CHOOSER_MODEL_HPP

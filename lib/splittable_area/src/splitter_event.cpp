#include <splittable_area/splitter_event.hpp>

namespace IDE
{
QEvent::Type SplitterEvent::s_type = QEvent::None;

SplitterEvent::SplitterEvent(SplitterSide side, int value)
  : QEvent(SplitterEvent::type())
  , _side(side)
  , _value(value)
{}

SplitterSide SplitterEvent::side() const
{
  return _side;
}

int SplitterEvent::value() const
{
  return _value;
}

QEvent::Type SplitterEvent::type()
{
  if(s_type == QEvent::None)
  {
    int t = QEvent::registerEventType();
    s_type = static_cast<QEvent::Type>(t);
  }
  return s_type;
}

} // namespace IDE

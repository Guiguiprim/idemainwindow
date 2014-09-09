#ifndef IDE_SPLITTER_EVENT_HPP
#define IDE_SPLITTER_EVENT_HPP

#include <QEvent>

#include "splitter_enum.hpp"

namespace IDE
{

class SplitterEvent : public QEvent
{
public:
  SplitterEvent(SplitterSide side, int value);

  SplitterSide side() const;
  int value() const;

  static QEvent::Type type();

private:
  static QEvent::Type s_type;
  SplitterSide _side;
  int _value;
};

} // namespace IDE

#endif // IDE_SPLITTER_EVENT_HPP

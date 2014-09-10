#include <splittable_area/splitter_widget_base.hpp>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_handler.hpp>

namespace IDE
{

SplitterWidgetBase::SplitterWidgetBase(SplitterArea* splitterArea)
  : QWidget(splitterArea)
  , _splitterArea(splitterArea)
{
  for(int i=0; i<4; ++i)
    _handlers[i] = NULL;
}

SplitterHandler* SplitterWidgetBase::handler(SplitterSide side) const
{
  return _handlers[side];
}

void SplitterWidgetBase::setPos(int left, int top, int right, int bottom)
{
  int width = right - left;
  int height = bottom - top;
  this->move(left, top);
  this->resize(width, height);
}

void SplitterWidgetBase::setTopPos(int top)
{
  // top side move => y move + height change
  int diff = this->pos().y() - top;
  this->move(this->pos().x(), top);
  this->resize(this->width(), this->height() + diff);
}

void SplitterWidgetBase::setBottomPos(int bottom)
{
  // bottom side move => height change
  int diff = bottom - this->pos().y() - this->height();
  this->resize(this->width(), this->height() + diff);
}

void SplitterWidgetBase::setLeftPos(int left)
{
  // left side move => y move + width change
  int diff = this->pos().x() - left;
  this->move(left, this->pos().y());
  this->resize(this->width() + diff, this->height());
}

void SplitterWidgetBase::setRightPos(int right)
{
  // right side move => width change
  int diff = right - this->pos().x() - this->width();
  this->resize(this->width() + diff, this->height());
}

void SplitterWidgetBase::setHandler(SplitterSide side, SplitterHandler* handler)
{
  SplitterHandler* old = _handlers[side];
  if(old == handler)
    return;

  if(old)
  {
    old->removeHandleWidget(this);
    disconnect(old, SIGNAL(destroyed(QObject*)),
               this, SLOT(xOnHandlerDestroy(QObject*)));
  }

  _handlers[side] = handler;

  if(handler)
  {
    handler->addHandleWidget(side, this);
    connect(handler, SIGNAL(destroyed(QObject*)),
            this, SLOT(xOnHandlerDestroy(QObject*)));
  }
}

void SplitterWidgetBase::xOnHandlerDestroy(QObject* obj)
{
  SplitterHandler* handler =  static_cast<SplitterHandler*>(obj);
  for(int i=0; i<4; ++i)
  {
    if(_handlers[i] == handler)
      _handlers[i] = NULL;
  }
}

} // namespace IDE

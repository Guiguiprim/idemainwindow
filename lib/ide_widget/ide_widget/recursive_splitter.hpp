#ifndef IDE_RECURSIVE_SPLITTER_HPP
#define IDE_RECURSIVE_SPLITTER_HPP

#include "api.hpp"
#include <QVector>

#include "splitter.hpp"

namespace IDE
{
class ClosableWidget;

//class RecursiveIndex : public QVector<int> {};
typedef QVector<int> RecursiveIndex;

class IDE_WIDGET_LIB_EXPORT RecursiveSplitter : public Splitter
{
  Q_OBJECT
public:
  explicit RecursiveSplitter(
      QWidget *parent = NULL);
  explicit RecursiveSplitter(
      const Qt::Orientation orientation,
      QWidget *parent = NULL);

  virtual bool eventFilter(
      QObject* watched,
      QEvent* event);

  bool addWidget(
      ClosableWidget* widget,
      const Qt::Orientation orientation = Qt::Horizontal,
      const RecursiveIndex& index = RecursiveIndex());
  RecursiveIndex indexOf(
      QWidget* widget) const;
  bool insertWidget(
      const RecursiveIndex& index,
      ClosableWidget* widget,
      const Qt::Orientation orientation);

  /**
   * @brief removeWidget: Remove the widget from the splitter
   * @param widget: Widget to remove
   * @param newParent: New parent to give to the widget
   * @return true if the widget as been removed (e.g. found)
   */
  bool removeWidget(
      QWidget* widget,
      QWidget* newParent = NULL);

  /**
   * @brief removeWidget: Remove the widget from the splitter
   * @param index: Index of the widget to remove
   * @param newParent: New parent to give to the widget
   * @return The widget removed
   */
  QWidget* removeWidget(
      const RecursiveIndex& index,
      QWidget* newParent = NULL);

  bool isSplitter(
      const RecursiveIndex& index) const;
  RecursiveSplitter* recursiveSplitter(
      const RecursiveIndex& index) const;
  QWidget* widgetAt(
      const RecursiveIndex& index) const;

  RecursiveSplitter* rootRecursiveSplitter() const;

  //@TODO: add allowed split
  //@TODO: split factory
};

} // namespace IDE

#endif // IDE_RECURSIVE_SPLITTER_HPP

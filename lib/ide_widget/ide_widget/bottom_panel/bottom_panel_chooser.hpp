#ifndef IDE_BOTTOM_PANEL_CHOOSER_HPP
#define IDE_BOTTOM_PANEL_CHOOSER_HPP

#include <QToolBar>
#include <QMap>

class QSignalMapper;
class QMenu;

namespace IDE
{
class BottomPanel;
class ClosableWidgetElement;

class BottomPanelChooser : public QToolBar
{
  Q_OBJECT
public:
  struct WidgetAction {
    QAction* openAction;
    QAction* displayAction;
    QString name;
    WidgetAction() : openAction(NULL), displayAction(NULL) {}
    ~WidgetAction();
  };

public:
  explicit BottomPanelChooser(BottomPanel* bottomPanel, QWidget *parent = NULL);
  ~BottomPanelChooser();

  void registerWidget(QWidget *widget, const QString& name, bool display = true);
  void registerWidget(ClosableWidgetElement *widget, bool display = true);

private Q_SLOTS:
  void xOnDisplayTriggered(QWidget*);
  void xOnOpenTriggered(QWidget*);

private:
  BottomPanel* _bottomPanel;
  QMenu* _displayMenu;
  QAction* _menuAction;
  QSignalMapper* _openMap;
  QSignalMapper* _displayMap;
  QMap<QWidget*, WidgetAction*> _widgetActions;
};

} // namespace IDE

#endif // IDE_BOTTOM_PANEL_CHOOSER_HPP

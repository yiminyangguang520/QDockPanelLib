#include "QDockManager.h"
#include "QDockFrame.h"
#include "QDockPanel.h"
#include <cassert>
#include "QDockNode.h"
#include <QList>
#include "QDockMaskWidget.h"
#include "QDockTabWidget.h"

QDockManager::QDockManager(QWidget *parent)
	: QObject(parent),dockFrmae_(new QDockFrame(this,parent))
{

}

QDockManager::~QDockManager()
{

}

QDockPanel* QDockManager::addPanel(int id, const QString& title,QPoint pos,QSize size, QWidget* contensWidget /*= NULL*/)
{
	if (dockPanels_.find(id) != dockPanels_.end())
	{
		return NULL;
	}
	QDockPanel* p = new QDockPanel(this,dockFrmae_);
	p->setId(id);
	p->setWindowTitle(title);
	p->resetContensWidget(contensWidget);
	p->move(pos);
	p->resize(size);
	p->show();
	dockPanels_.insert(std::make_pair(id,p));

	return p;
}

QDockPanel* QDockManager::getDockPanelByID( int id )
{
	std::map<int,QDockPanel*>::iterator it = dockPanels_.find(id);
	if (it == dockPanels_.end())
	{
		return NULL;
	}

	return it->second;
}

bool QDockManager::dockPanelToFrame( QDockPanel* panel,DockArea area )
{
	switch (area)
	{
	case LeftArea:
		{
			QList<int> sizes;
			sizes.push_back(30);
			sizes.push_back(70);

			int c = dockFrmae_->rootNode_->count();
			if (c == 1)
			{
				dockFrmae_->rootNode_->setOrientation(Qt::Horizontal);
				panel->setDockStatus();
 				dockFrmae_->rootNode_->insertWidget(0,panel);
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else if (c == 2)
			{
				QDockNode* tmpNode = dockFrmae_->rootNode_;
				panel->setDockStatus();
				dockFrmae_->rootNode_ = new QDockNode(dockFrmae_);
				dockFrmae_->rootNode_->setOrientation(Qt::Horizontal);
				dockFrmae_->rootNode_->insertWidget(0,panel);
				dockFrmae_->rootNode_->insertWidget(1,tmpNode);
				dockFrmae_->relayout();
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else
			{
				assert(false);
			}
			break;
		}
	case TopArea:
		{
			QList<int> sizes;
			sizes.push_back(30);
			sizes.push_back(70);

			int c = dockFrmae_->rootNode_->count();
			if (c == 1)
			{
				dockFrmae_->rootNode_->setOrientation(Qt::Vertical);
				panel->setDockStatus();
				dockFrmae_->rootNode_->insertWidget(0,panel);
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else if (c == 2)
			{
				QDockNode* tmpNode = dockFrmae_->rootNode_;
				panel->setDockStatus();
				dockFrmae_->rootNode_ = new QDockNode(dockFrmae_);
				dockFrmae_->rootNode_->setOrientation(Qt::Vertical);
				dockFrmae_->rootNode_->insertWidget(0,panel);
				dockFrmae_->rootNode_->insertWidget(1,tmpNode);
				dockFrmae_->relayout();
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else
			{
				assert(false);
			}
			break;
		}
	case RightArea:
		{
			QList<int> sizes;
			sizes.push_back(70);
			sizes.push_back(30);

			int c = dockFrmae_->rootNode_->count();
			if (c == 1)
			{
				dockFrmae_->rootNode_->setOrientation(Qt::Horizontal);
				panel->setDockStatus();
				dockFrmae_->rootNode_->insertWidget(1,panel);
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else if (c == 2)
			{
				QDockNode* tmpNode = dockFrmae_->rootNode_;
				panel->setDockStatus();
				dockFrmae_->rootNode_ = new QDockNode(dockFrmae_);
				dockFrmae_->rootNode_->setOrientation(Qt::Horizontal);
				dockFrmae_->rootNode_->insertWidget(0,tmpNode);
				dockFrmae_->rootNode_->insertWidget(1,panel);
				dockFrmae_->relayout();
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else
			{
				assert(false);
			}
			break;
		}
	case BottomArea:
		{
			QList<int> sizes;
			sizes.push_back(70);
			sizes.push_back(30);

			int c = dockFrmae_->rootNode_->count();
			if (c == 1)
			{
				dockFrmae_->rootNode_->setOrientation(Qt::Vertical);
				panel->setDockStatus();
				dockFrmae_->rootNode_->insertWidget(0,panel);
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else if (c == 2)
			{
				QDockNode* tmpNode = dockFrmae_->rootNode_;
				panel->setDockStatus();
				dockFrmae_->rootNode_ = new QDockNode(dockFrmae_);
				dockFrmae_->rootNode_->setOrientation(Qt::Vertical);
				dockFrmae_->rootNode_->insertWidget(0,tmpNode);
				dockFrmae_->rootNode_->insertWidget(1,panel);
				dockFrmae_->relayout();
				dockFrmae_->rootNode_->setSizes(sizes);
			}
			else
			{
				assert(false);
			}
			break;
		}
	case CenterArea:
		assert(dockFrmae_->rootNode_->count() == 0);
		panel->setDockStatus();
		panel->setParent(dockFrmae_->rootNode_);
		break;
	default:
		return false;
	}

	return true;
}

bool QDockManager::dockPanelToPanel( QDockPanel* from,QDockPanel* target, DockArea area )
{
	QList<int> sizes;
	sizes.push_back(5);
	sizes.push_back(5);

	if (target->isDocked())
	{
		QDockNode* parentNode = qobject_cast<QDockNode*>(target->parentWidget());
		if (parentNode)
		{
			if (parentNode->count() == 1)
			{
				assert(isRootNode(parentNode));
				switch (area)
				{
				case CenterLeftArea:
					from->setDockStatus();
					parentNode->setOrientation(Qt::Horizontal);
					parentNode->insertWidget(0,from);
					parentNode->setSizes(sizes);
					break;
				case CenterTopArea:
					from->setDockStatus();
					parentNode->setOrientation(Qt::Vertical);
					parentNode->insertWidget(0,from);
					parentNode->setSizes(sizes);
					break;
				case CenterRightArea:
					from->setDockStatus();
					parentNode->setOrientation(Qt::Horizontal);
					parentNode->insertWidget(1,from);
					parentNode->setSizes(sizes);
					break;
				case CenterBottomArea:
					from->setDockStatus();
					parentNode->setOrientation(Qt::Vertical);
					parentNode->insertWidget(1,from);
					parentNode->setSizes(sizes);
					break;
				case CenterArea:
					{
						QDockPanel* tabPanel = new QDockPanel(this,dockFrmae_);
						tabPanel->setAcceptDrops(false);
						QDockTabWidget* tabWidget = new QDockTabWidget(tabPanel);
						tabPanel->resetContensWidget(tabWidget);
						tabWidget->addTab(target,target->windowTitle());
						from->setDockStatus();
						from->setTabbedStatus(true,tabPanel);
						tabWidget->addTab(from,from->windowTitle());
						target->setTabbedStatus(true,tabPanel);
						tabPanel->resize(target->size());
						tabPanel->setDockStatus();
						parentNode->insertWidget(0,tabPanel);
						connect(tabWidget,SIGNAL(setBasePanelTitle(const QString&)),tabPanel,SLOT(setWindowTitle(const QString &)));
						tabPanel->setWindowTitle(tabWidget->currentWidget()->windowTitle());
					}
					break;
				default:
					return false;
				}
				return true;
			}

			int parentIndex = parentNode->indexOf(target);
			QList<int> parentSizes = parentNode->sizes();

			QDockNode* node = new QDockNode(NULL);
			switch (area)
			{
			case CenterLeftArea:
				from->setDockStatus();
				node->setOrientation(Qt::Horizontal);
				node->insertWidget(0,from);
				node->insertWidget(1,target);
				node->setSizes(sizes);
				parentNode->insertWidget(parentIndex,node);
				parentNode->setSizes(parentSizes);
				break;
			case CenterTopArea:
				from->setDockStatus();
				node->setOrientation(Qt::Vertical);
				node->insertWidget(0,from);
				node->insertWidget(1,target);
				node->setSizes(sizes);
				parentNode->insertWidget(parentIndex,node);
				parentNode->setSizes(parentSizes);
				break;
			case CenterRightArea:
				from->setDockStatus();
				node->setOrientation(Qt::Horizontal);
				node->insertWidget(0,target);
				node->insertWidget(1,from);
				node->setSizes(sizes);
				parentNode->insertWidget(parentIndex,node);
				parentNode->setSizes(parentSizes);
				break;
			case CenterBottomArea:
				from->setDockStatus();
				node->setOrientation(Qt::Vertical);
				node->insertWidget(0,target);
				node->insertWidget(1,from);
				node->setSizes(sizes);
				parentNode->insertWidget(parentIndex,node);
				parentNode->setSizes(parentSizes);
				break;
			case CenterArea:
				{
					QDockPanel* tabPanel = new QDockPanel(this,dockFrmae_);
					tabPanel->setAcceptDrops(false);
					QDockTabWidget* tabWidget = new QDockTabWidget(tabPanel);
					tabPanel->resetContensWidget(tabWidget);
					tabWidget->addTab(target,target->windowTitle());
					from->setDockStatus();
					from->setTabbedStatus(true,tabPanel);
					tabWidget->addTab(from,from->windowTitle());
					target->setTabbedStatus(true,tabPanel);
					tabPanel->resize(target->size());
					tabPanel->setDockStatus();
					parentNode->insertWidget(parentIndex,tabPanel);
					parentNode->setSizes(sizes);
					connect(tabWidget,SIGNAL(setBasePanelTitle(const QString&)),tabPanel,SLOT(setWindowTitle(const QString &)));
					tabPanel->setWindowTitle(tabWidget->currentWidget()->windowTitle());
				}
				break;
			default:
				return false;
			}

			return true;
		}

		if (target->isTabbed_)
		{
			switch (area)
			{
			case CenterArea:
				{
					QDockTabWidget* tabWidget = qobject_cast<QDockTabWidget*>(target->parentTabPanel_->contensWidget_);
					from->setDockStatus();
					from->setTabbedStatus(true,target->parentTabPanel_);
					tabWidget->addTab(from,from->windowTitle());
				}
				break;
			case CenterLeftArea:
			case CenterTopArea:
			case CenterRightArea:
			case CenterBottomArea:
				dockPanelToPanel(from,target->parentTabPanel_,area);
				break;
			}

			return true;
		}

		assert(false);
		return false;
	}
	else
	{

	}

	return false;
}

bool QDockManager::isRootNode( QDockNode* node )
{
	return node == dockFrmae_->rootNode_;
}

void QDockManager::undockPanel( QDockPanel* panel )
{
	QDockNode* parentNode = qobject_cast<QDockNode*>(panel->parentWidget());
	if (parentNode)
	{
		panel->setParent(dockFrmae_);
		panel->setFloatStatus();
		if (isRootNode(parentNode))
		{
			QDockNode* otherChildNode = qobject_cast<QDockNode*>(parentNode->widget(0));
			if (otherChildNode)
			{
				QList<int> sizes = otherChildNode->sizes();
				parentNode->setOrientation(otherChildNode->orientation());
				parentNode->insertWidget(0,otherChildNode->widget(0));
				parentNode->insertWidget(1,otherChildNode->widget(0));
				parentNode->setSizes(sizes);
				otherChildNode->deleteLater();
			}
			return;
		}

		assert(parentNode->count() == 1);
		QDockNode* grandParentNode = qobject_cast<QDockNode*>(parentNode->parentWidget());
		assert(grandParentNode);
		QList<int> sizes = grandParentNode->sizes();
		QWidget* widget = parentNode->widget(0);
		int index = grandParentNode->indexOf(parentNode);
		parentNode->close();
		parentNode->deleteLater();
		grandParentNode->insertWidget(index,widget);
		grandParentNode->setSizes(sizes);

		return;
	}

	panel->setParent(dockFrmae_);
	panel->setFloatStatus();

	return;
}

void QDockManager::onDragEnterPanel()
{
	dockFrmae_->onDragEnterPanel();
}

void QDockManager::onDragLeavePanel()
{
	dockFrmae_->onDragLeavePanel();
}

void QDockManager::onEndDragAtPanel()
{
	dockFrmae_->onEndDragAtPanel();
}

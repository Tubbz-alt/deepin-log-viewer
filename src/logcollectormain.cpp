#include "logcollectormain.h"

#include <DApplication>
#include <DTitlebar>
#include <QDebug>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>

DWIDGET_USE_NAMESPACE

LogCollectorMain::LogCollectorMain(QWidget *parent)
    : DMainWindow(parent)
{
    initUI();
    initConnection();
}

LogCollectorMain::~LogCollectorMain()
{
    /** delete when app quit */
    if (m_searchEdt) {
        delete m_searchEdt;
        m_searchEdt = nullptr;
    }
}

void LogCollectorMain::initUI()
{
    /** add searchEdit */
    m_searchEdt = new DSearchEdit;
    m_searchEdt->setPlaceHolder(DApplication::translate("SearchBar", "Search"));
    m_searchEdt->setMaximumWidth(400);
    titlebar()->setCustomWidget(m_searchEdt, true);

    /** add titleBar */
    titlebar()->setIcon(QIcon("://images/logo.svg"));
    titlebar()->setTitle("");

    /** menu */
    //    titlebar()->menu()->addAction(new QAction(tr("help")));

    /** inherit QMainWidow, why need new centralWidget?? */
    this->setCentralWidget(new DWidget());

    m_hLayout = new QHBoxLayout(this->centralWidget());
    m_hSplitter = new QSplitter(this->centralWidget());
    m_hSplitter->setOrientation(Qt::Horizontal);

    /** left frame */
    //    m_treeView = new LogTreeView(m_hSplitter);
    m_treeView = new LogListView(m_hSplitter);
    m_hSplitter->addWidget(m_treeView);

    QWidget *layoutWidget = new QWidget(m_hSplitter);

    m_vLayout = new QVBoxLayout(layoutWidget);

    /** topRight frame */
    m_topRightWgt = new FilterContent(layoutWidget);
    m_vLayout->addWidget(m_topRightWgt);

    /** midRight frame */
    m_midRightWgt = new DisplayContent(layoutWidget);
    m_vLayout->addWidget(m_midRightWgt, 1);

    m_hSplitter->addWidget(layoutWidget);

    m_hLayout->addWidget(m_hSplitter);

    m_hSplitter->setStretchFactor(0, 5);
    m_hSplitter->setStretchFactor(1, 15);

#if 0
    // filter button
    DPushButton *filterBtn = new DPushButton("filter");
    filterBtn->setCheckable(true);
    filterBtn->setChecked(true);
    titlebar()->addWidget(filterBtn);
    connect(filterBtn, &DPushButton::clicked, this, [=](bool checked) {
        if (checked) {
            m_topRightWgt->show();
        } else {
            m_topRightWgt->hide();
        }
    });
#endif
}

void LogCollectorMain::initConnection()
{
    //! search
    connect(m_searchEdt, &DSearchEdit::textChanged, m_midRightWgt,
            &DisplayContent::slot_searchResult);

    //! filter widget
    connect(m_topRightWgt, SIGNAL(sigButtonClicked(int, int, QModelIndex)), m_midRightWgt,
            SLOT(slot_BtnSelected(int, int, QModelIndex)));

    connect(m_topRightWgt, &FilterContent::sigCbxAppIdxChanged, m_midRightWgt,
            &DisplayContent::slot_appLogs);

    connect(m_topRightWgt, &FilterContent::sigExportInfo, m_midRightWgt,
            &DisplayContent::slot_exportClicked);

    //! treeView widget
    connect(m_treeView, SIGNAL(clicked(const QModelIndex &)), m_midRightWgt,
            SLOT(slot_treeClicked(const QModelIndex &)));
    //! set tree <==> combobox visible
    connect(m_treeView, SIGNAL(clicked(const QModelIndex &)), m_topRightWgt,
            SLOT(slot_treeClicked(const QModelIndex &)));
}
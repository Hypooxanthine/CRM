#include "../../include/HUD/contactentry.h"

#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

#include "DataStructures/contact.h"

ContactEntry::ContactEntry(QWidget *parent, const Contact& c)
    : QWidget(parent), layout(new QHBoxLayout(this)),
      lPhoto(new QLabel(this)), lName(new QLabel(this)),
      bEdit(new QPushButton(this)), bDelete(new QPushButton(this))
{
    bEdit->setText(tr("Edit"));
    bDelete->setText(tr("Delete"));

    layout->setContentsMargins(0,0,0,0);

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);

    sp.setHorizontalStretch(2);
    lPhoto->setSizePolicy(sp);
    layout->addWidget(lPhoto);

    sp.setHorizontalStretch(10);
    lPhoto->setSizePolicy(sp);
    layout->addWidget(lName);

    sp.setHorizontalStretch(1);
    lPhoto->setSizePolicy(sp);
    layout->addWidget(bEdit);

    sp.setHorizontalStretch(1);
    lPhoto->setSizePolicy(sp);
    layout->addWidget(bDelete);

    setContact(c);

    QWidget::connect(bDelete, SIGNAL(clicked()), this, SLOT(emitDeleted()));
}

void ContactEntry::setContact(const Contact& c)
{
    QImage img;
    if(img.load(c.getPhotoPath().c_str()))
    {
        lPhoto->setPixmap(QPixmap::fromImage(img));
    }

    lName->setText(QString::fromStdString(c.getFirstName() + " " + c.getLastName()));
}

void ContactEntry::emitDeleted()
{
    emit deleted(contact);
}

void ContactEntry::openEditContact(const Contact& c)
{

}

/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerMRThermometryFooBarWidget.h"
#include "ui_qSlicerMRThermometryFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_MRThermometry
class qSlicerMRThermometryFooBarWidgetPrivate
  : public Ui_qSlicerMRThermometryFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerMRThermometryFooBarWidget);
protected:
  qSlicerMRThermometryFooBarWidget* const q_ptr;

public:
  qSlicerMRThermometryFooBarWidgetPrivate(
    qSlicerMRThermometryFooBarWidget& object);
  virtual void setupUi(qSlicerMRThermometryFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerMRThermometryFooBarWidgetPrivate
::qSlicerMRThermometryFooBarWidgetPrivate(
  qSlicerMRThermometryFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerMRThermometryFooBarWidgetPrivate
::setupUi(qSlicerMRThermometryFooBarWidget* widget)
{
  this->Ui_qSlicerMRThermometryFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerMRThermometryFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerMRThermometryFooBarWidget
::qSlicerMRThermometryFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerMRThermometryFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerMRThermometryFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerMRThermometryFooBarWidget
::~qSlicerMRThermometryFooBarWidget()
{
}

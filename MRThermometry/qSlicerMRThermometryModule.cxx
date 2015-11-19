/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Qt includes
#include <QtPlugin>

// MRThermometry Logic includes
#include <vtkSlicerMRThermometryLogic.h>

// MRThermometry includes
#include "qSlicerMRThermometryModule.h"
#include "qSlicerMRThermometryModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerMRThermometryModule, qSlicerMRThermometryModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerMRThermometryModulePrivate
{
public:
  qSlicerMRThermometryModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerMRThermometryModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerMRThermometryModulePrivate::qSlicerMRThermometryModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerMRThermometryModule methods

//-----------------------------------------------------------------------------
qSlicerMRThermometryModule::qSlicerMRThermometryModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerMRThermometryModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerMRThermometryModule::~qSlicerMRThermometryModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerMRThermometryModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerMRThermometryModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerMRThermometryModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerMRThermometryModule::icon() const
{
  return QIcon(":/Icons/MRThermometry.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerMRThermometryModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerMRThermometryModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerMRThermometryModule
::createWidgetRepresentation()
{
  return new qSlicerMRThermometryModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerMRThermometryModule::createLogic()
{
  return vtkSlicerMRThermometryLogic::New();
}

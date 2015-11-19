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
#include <QDebug>
#include <QString>

// SlicerQt includes
#include "qSlicerMRThermometryModuleWidget.h"
#include "ui_qSlicerMRThermometryModuleWidget.h"

#include "vtkMRMLScalarVolumeNode.h"

#include "vtkSlicerMRThermometryLogic.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerMRThermometryModuleWidgetPrivate: public Ui_qSlicerMRThermometryModuleWidget
{
public:
  qSlicerMRThermometryModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerMRThermometryModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerMRThermometryModuleWidgetPrivate::qSlicerMRThermometryModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerMRThermometryModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerMRThermometryModuleWidget::qSlicerMRThermometryModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerMRThermometryModuleWidgetPrivate )
{ 
}

//-----------------------------------------------------------------------------
qSlicerMRThermometryModuleWidget::~qSlicerMRThermometryModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::setup()
{
  Q_D(qSlicerMRThermometryModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  this->baselineNode = NULL;
  this->phaseImages.clear();
  this->echoTime = d->EchoTimeSpinbox->value();
  this->magneticField = d->MagneticFieldSpinbox->value();
  this->gyromagneticRatio = d->GyromagneticRatioSpinbox->value();
  this->thermalCoefficient = d->ThermalCoefficientSpinbox->value();
  this->siemensScalingFactor = d->SiemensScalingFactorSpinbox->value();
  this->baseTemperature = d->BaseTemperatureSpinbox->value();

  connect(d->BaselineImageSelector, SIGNAL(currentNodeChanged(vtkMRMLNode*)),
	  this, SLOT(onBaselineChanged(vtkMRMLNode*)));
  connect(d->PhaseImageSelector, SIGNAL(currentNodeChanged(vtkMRMLNode*)),
	  this, SLOT(onPhaseImageChanged(vtkMRMLNode*)));
  connect(d->AddImageButton, SIGNAL(clicked()),
	  this, SLOT(onAddImageClicked()));
  connect(d->RemoveImageButton, SIGNAL(clicked()),
	  this, SLOT(onRemoveImageClicked()));
  connect(d->EchoTimeSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onEchoTimeChanged(double)));
  connect(d->MagneticFieldSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onMagneticFieldChanged(double)));
  connect(d->GyromagneticRatioSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onGyromagneticRatioChanged(double)));
  connect(d->ThermalCoefficientSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onThermalCoefficientChanged(double)));
  connect(d->SiemensScalingFactorSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onSiemensScalingFactorChanged(double)));
  connect(d->BaseTemperatureSpinbox, SIGNAL(valueChanged(double)),
	  this, SLOT(onBaseTemperatureChanged(double)));
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onBaselineChanged(vtkMRMLNode* node)
{
  vtkMRMLScalarVolumeNode* bNode = vtkMRMLScalarVolumeNode::SafeDownCast(node);
  if (!bNode)
    {
    return;
    }

  this->baselineNode = bNode;
  this->computeTemperatureImage();
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onPhaseImageChanged(vtkMRMLNode* node)
{
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onAddImageClicked()
{
  Q_D(qSlicerMRThermometryModuleWidget);

  vtkMRMLScalarVolumeNode* pImage = vtkMRMLScalarVolumeNode::SafeDownCast(
    d->PhaseImageSelector->currentNode());
  if (!pImage)
    {
    return;
    }

  this->phaseImages.push_back(pImage);
  d->PhaseImageListWidget->addItem(QString(pImage->GetName()));
  this->computeTemperatureImage();
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onRemoveImageClicked()
{
  Q_D(qSlicerMRThermometryModuleWidget);

  int currentRow = d->PhaseImageListWidget->currentRow();
  if (currentRow >= 0 && currentRow < this->phaseImages.size())
    {
    this->phaseImages.erase(this->phaseImages.begin()+currentRow);
    d->PhaseImageListWidget->takeItem(currentRow);
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onEchoTimeChanged(double value)
{
  if (value != this->echoTime)
    {
    this->echoTime = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onMagneticFieldChanged(double value)
{
  if (value != this->magneticField)
    {
    this->magneticField = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onGyromagneticRatioChanged(double value)
{
  if (value != this->gyromagneticRatio)
    {
    this->gyromagneticRatio = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onThermalCoefficientChanged(double value)
{
  if (value != this->thermalCoefficient)
    {
    this->thermalCoefficient = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onSiemensScalingFactorChanged(double value)
{
  if (value != this->siemensScalingFactor)
    {
    this->siemensScalingFactor = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::onBaseTemperatureChanged(double value)
{
  if (value != this->baseTemperature)
    {
    this->baseTemperature = value;
    this->computeTemperatureImage();
    }
}

//-----------------------------------------------------------------------------
void qSlicerMRThermometryModuleWidget::computeTemperatureImage()
{
  Q_D(qSlicerMRThermometryModuleWidget);

  vtkSlicerMRThermometryLogic* mrtLogic = vtkSlicerMRThermometryLogic::SafeDownCast(
    this->logic());
  if (mrtLogic)
    {
    vtkMRMLScalarVolumeNode* outputImage = vtkMRMLScalarVolumeNode::SafeDownCast(
      d->OutputImageSelector->currentNode());
    if (!outputImage)
      {
      return;
      }

    mrtLogic->computeTemperatureImage(this->baselineNode,
				      this->phaseImages,
				      outputImage,
				      this->echoTime,
				      this->magneticField,
				      this->gyromagneticRatio,
				      this->thermalCoefficient,
				      this->siemensScalingFactor,
				      this->baseTemperature);
    }
}

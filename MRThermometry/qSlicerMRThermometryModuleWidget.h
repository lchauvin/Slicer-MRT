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

#ifndef __qSlicerMRThermometryModuleWidget_h
#define __qSlicerMRThermometryModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerMRThermometryModuleExport.h"

class qSlicerMRThermometryModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLScalarVolumeNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_MRTHERMOMETRY_EXPORT qSlicerMRThermometryModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerMRThermometryModuleWidget(QWidget *parent=0);
  virtual ~qSlicerMRThermometryModuleWidget();

public slots:
  void onBaselineChanged(vtkMRMLNode* node);
  void onPhaseImageChanged(vtkMRMLNode* node);
  void onAddImageClicked();
  void onRemoveImageClicked();
  void onEchoTimeChanged(double value);
  void onMagneticFieldChanged(double value);
  void onGyromagneticRatioChanged(double value);
  void onThermalCoefficientChanged(double value);
  void onSiemensScalingFactorChanged(double value);
  void onBaseTemperatureChanged(double value);

protected:
  QScopedPointer<qSlicerMRThermometryModuleWidgetPrivate> d_ptr;

  virtual void setup();
  void computeTemperatureImage();

  vtkMRMLScalarVolumeNode* baselineNode;
  std::vector< vtkMRMLScalarVolumeNode* > phaseImages;
  double echoTime;
  double magneticField;
  double gyromagneticRatio;
  double thermalCoefficient;
  double siemensScalingFactor;
  double baseTemperature;

private:
  Q_DECLARE_PRIVATE(qSlicerMRThermometryModuleWidget);
  Q_DISABLE_COPY(qSlicerMRThermometryModuleWidget);
};

#endif

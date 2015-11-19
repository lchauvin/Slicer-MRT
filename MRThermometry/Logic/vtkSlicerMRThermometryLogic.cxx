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

// MRThermometry Logic includes
#include "vtkSlicerMRThermometryLogic.h"

// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkMatrix4x4.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerMRThermometryLogic);

//----------------------------------------------------------------------------
vtkSlicerMRThermometryLogic::vtkSlicerMRThermometryLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerMRThermometryLogic::~vtkSlicerMRThermometryLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic::RegisterNodes()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerMRThermometryLogic::computeTemperatureImage(vtkMRMLScalarVolumeNode* baselineImage,
							  std::vector< vtkMRMLScalarVolumeNode* >& phaseImages,
							  vtkMRMLScalarVolumeNode* outputImage,
							  double echoTime,
							  double magneticField,
							  double gyromagneticRatio,
							  double thermalCoefficient,
							  double siemensScalingFactor,
							  double baseTemperature)
{
  vtkImageData* baselineImageData = baselineImage->GetImageData();
  if (!baselineImageData)
    {
    return;
    }

  if (phaseImages.size() <= 0)
    {
    return;
    }


  // Create new output data base on baseline image data
  int dimensions[3] = {0,0,0};
  baselineImageData->GetDimensions(dimensions);
  vtkSmartPointer<vtkMatrix4x4> ijkToRasMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
  baselineImage->GetIJKToRASDirectionMatrix(ijkToRasMatrix.GetPointer());

  outputImage->SetOrigin(baselineImage->GetOrigin());
  outputImage->SetSpacing(baselineImage->GetSpacing());
  outputImage->SetIJKToRASDirectionMatrix(ijkToRasMatrix.GetPointer());

  vtkImageData* outputImageData = vtkImageData::New();
  outputImageData->SetDimensions(dimensions);
  outputImageData->AllocateScalars(VTK_DOUBLE, baselineImageData->GetNumberOfScalarComponents());
  //double* outputBuffer = (double*) outputImageData->GetPointData()->GetScalars()->GetVoidPointer(0);

  // Temp image
  vtkImageData* sumPhaseDifference = vtkImageData::New();
  sumPhaseDifference->SetDimensions(dimensions);
  sumPhaseDifference->AllocateScalars(VTK_DOUBLE, baselineImageData->GetNumberOfScalarComponents());
  //unsigned short* sumBuffer = (unsigned short*) sumPhaseDifference->GetPointData()->GetScalars()->GetVoidPointer(0);

  for (int i = 0; i < dimensions[0]; ++i)
    {
    for (int j = 0; j < dimensions[1]; ++j)
      {
      for (int k = 0; k < dimensions[2]; ++k)
	{
	sumPhaseDifference->SetScalarComponentFromDouble(i,j,k,0,0);
	}
      }
    }


/*
// Faster method, but memory management more tricky

  int extent[6];
  outputImageData->GetExtent(extent);

  vtkIdType inc[3];
  outputImageData->GetIncrements(inc);

  for (int pIm = 0; pIm < phaseImages.size(); ++pIm)
    {
    vtkImageData *im1, *im2;
    if (pIm == 0)
      {
      im1 = baselineImageData;
      im2 = phaseImages[0]->GetImageData();
      }
    else
      {
      im1 = phaseImages[pIm-1]->GetImageData();
      im2 = phaseImages[pIm]->GetImageData();
      }

    if (!im1 || !im2 || (im1 == im2))
      {
      return;
      }

    unsigned short* im1Buffer = (unsigned short*) im1->GetPointData()->GetScalars()->GetVoidPointer(0);
    unsigned short* im2Buffer = (unsigned short*) im2->GetPointData()->GetScalars()->GetVoidPointer(0);

    if (!im1Buffer || !im2Buffer)
      {
      return;
      }

    for (int k=0; k < extent[5]+1; ++k)
      {
      for (int j=0; j < extent[3]+1; ++j)
	{
	for (int i=0; i < extent[1]+1; ++i)
	  {
	  unsigned short phaseDiff = im2Buffer[k*inc[2]+j*inc[1]+i] - im1Buffer[k*inc[2]+j*inc[1]+i];
	  sumBuffer[k*inc[2]+j*inc[1]+i] += phaseDiff;
	  double coefficient = 1 / (echoTime * 2*M_PI*gyromagneticRatio * magneticField * thermalCoefficient);
	  double temp = baseTemperature + (sumBuffer[k*inc[2]+j*inc[1]+i] * M_PI / siemensScalingFactor) * coefficient;
	  outputBuffer[k*inc[2]+j*inc[1]+i] = temp;
	  }
	}
      }
    }
*/
  
  for (int pIm = 0; pIm < phaseImages.size(); ++pIm)
    {
    vtkImageData *im1 = NULL;
    vtkImageData *im2 = NULL;
    if (pIm == 0)
      {
      im1 = baselineImageData;
      im2 = phaseImages[0]->GetImageData();
      }
    else
      {
      im1 = phaseImages[pIm-1]->GetImageData();
      im2 = phaseImages[pIm]->GetImageData();
      }

    if (!im1 || !im2 || (im1 == im2))
      {
      return;
      }

    for (int i = 0; i < dimensions[0]; ++i)
      {
      for (int j = 0; j < dimensions[1]; ++j)
	{
	for (int k = 0; k < dimensions[2]; ++k)
	  {
	  unsigned short diff = im2->GetScalarComponentAsDouble(i,j,k,0) - im1->GetScalarComponentAsDouble(i,j,k,0);
	  double currentDiff = sumPhaseDifference->GetScalarComponentAsDouble(i,j,k,0);
	  sumPhaseDifference->SetScalarComponentFromDouble(i,j,k,0, currentDiff+(double)(diff));
	  double coefficient = 1 / (echoTime * 2*M_PI*gyromagneticRatio * magneticField * thermalCoefficient);
	  double temp = baseTemperature + (sumPhaseDifference->GetScalarComponentAsDouble(i,j,k,0) * M_PI / siemensScalingFactor) * coefficient;
	  outputImageData->SetScalarComponentFromDouble(i,j,k,0, temp);
	  }
	}
      }
    }

  sumPhaseDifference->Delete();
  outputImage->SetAndObserveImageData(outputImageData);
}

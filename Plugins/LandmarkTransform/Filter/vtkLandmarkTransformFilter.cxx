#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkIterativeClosestPointTransform.h"
#include "vtkLandmarkTransform.h"
#include "vtkObjectFactory.h" //for new() macro
#include "vtkPolyData.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"

#include "vtkLandmarkTransformFilter.h"

vtkStandardNewMacro(vtkLandmarkTransformFilter);

//-----------------------------------------------------------------------------
vtkLandmarkTransformFilter::vtkLandmarkTransformFilter()
{
  this->SetNumberOfInputPorts(3);
}

//-----------------------------------------------------------------------------
vtkLandmarkTransformFilter::~vtkLandmarkTransformFilter() {}

//----------------------------------------------------------------------------
int vtkLandmarkTransformFilter::FillInputPortInformation(int port, vtkInformation* info)
{
  if (!this->Superclass::FillInputPortInformation(port, info))
  {
    return 0;
  }

  // The two point sets can be any DataSet type
  if (port == 0 || port == 1)
  {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
    return 1;
  }

  // The source dataset must be a polydata as we use vtkTransformPolyDataFilter to apply the
  // transformation
  if (port == 2)
  {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPolyData");
    return 1;
  }
  return 0;
}

//----------------------------------------------------------------------------
int vtkLandmarkTransformFilter::RequestData(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  // get the info objects
  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  // get the input and output
  vtkPolyData* input = vtkPolyData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData* output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  // ICP Transform
  this->LandmarkTransform = vtkSmartPointer<vtkLandmarkTransform>::New();

  vtkPoints* SourceLandmarks =
    static_cast<vtkPolyData*>(this->GetExecutive()->GetInputData(0, 0))->GetPoints();
  vtkPoints* TargetLandmarks =
    static_cast<vtkPolyData*>(this->GetExecutive()->GetInputData(1, 0))->GetPoints();

  std::cout << "Number of source landmarks: " << SourceLandmarks->GetNumberOfPoints() << std::endl;
  std::cout << "Number of target landmarks: " << TargetLandmarks->GetNumberOfPoints() << std::endl;

  this->LandmarkTransform->SetSourceLandmarks(SourceLandmarks);
  this->LandmarkTransform->SetTargetLandmarks(TargetLandmarks);

  // this->LandmarkTransform->SetModeToRigidBody();
  this->LandmarkTransform->Update();

  // std::cout << "Landmark transform: " << *(this->LandmarkTransform) << std::endl;

  // bring the source to the target
  vtkSmartPointer<vtkTransformPolyDataFilter> TransformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  vtkPolyData* SourceDataset = static_cast<vtkPolyData*>(this->GetExecutive()->GetInputData(2, 0));

  TransformFilter->SetInputData(SourceDataset);
  TransformFilter->SetTransform(this->LandmarkTransform);
  TransformFilter->Update();

  output->ShallowCopy(TransformFilter->GetOutput());

  return 1;
}

void vtkLandmarkTransformFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkPolyDataAlgorithm::PrintSelf(os, indent);
}

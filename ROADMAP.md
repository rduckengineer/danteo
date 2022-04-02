```mermaid
graph
  classDef done fill:#1A1,color:#111;
  classDef inprogress fill:#C81,color:#111;

  game([Game]) --> StateMachine
  game --> PageSwitching
  PageSwitching --> PagePresenter
  PageSwitching --> StateMachine
  PagePresenter --> PlainTextPage
  game --> RenderLoop
  PagePresenter --> RenderLoop
  
  class , done;
  class PlainTextPage inprogress;
```
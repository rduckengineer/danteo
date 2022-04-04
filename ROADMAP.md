```mermaid
graph
  classDef done fill:#1A1,color:#111;
  classDef inprogress fill:#C81,color:#111;

  game([Game]) --> StateMachine
  game --> RenderLoop

  RenderLoop --> PageSwitching

  PageSwitching --> PresentElement
  PageSwitching --> StateMachine
  
  PresentElement --> PlainTextPage
  PresentElement --> TitlePage

  TitlePage --> HSVColor
  TitlePage --> Size2D

  class PageSwitching, inprogress;
  class PlainTextPage,TitlePage,PresentElement,HSVColor,Size2D done;
```

## AUTOGRAD MECHANICS

This note will present an overview of how `autograd` works and records the operations. It's not strictly necessary to understand all this, but we recommend getting familiar with it, as it will help you write more efficient, cleaner programs, and can aid you in debugging.

### Excluding subgraphs from the backward

Every Tensor has a flag: `requires_grad` that allows for fine grained exclusion of subgraphs from gradient computation and can increase efficiency.

## `requires_grad`

If there is a single input ot an operation that requires gradient, its output wll also require gradient. Conversely, only if all inputs don't require gradient, the output will also not require it. Backward computation is never performed in the subgraphs, where all Tensors don't require gradients.

```python
import torch

x = torch.randn(5, 5)       # requires_grad=False by default
y = torch.randn(5, 5)       # requires_grad=False by default
z = torch.randn((5, 5), requires_grad=True)

a = x + y
a.requires_grad
# False

b = a + z
b.requires_grad
# True
```

This is especially useful when you want to freeze part of your model, or you know in advance that you're not going to use gradients w.r.t. some parameters. For example if you want to finetune a pretrained CNN, it's enough to switch the `requires_grad` flasgs in the frozen base, and no intermediate buffers will be saved, until the computation gets to the last layer, where the affine transform will use weights that require gradient, and the output of the network will also require them.

```python
import torch
import torchvision

model = torchvision.models.resnet18(petrained=true)
for param in model.parameters():
    param.requires_grad = False

# Code to replace the last fully connected layer
# Parameters of newly constructed modules have requires_grad=True by default

model.fc = nn.Linear(512, 100)

# Optimize only the classifier
optimizer = optim.SGD(model.fc.parameters(), lr=1e-2, momentum=0.9)
```

## How autograd encodes the history

Autograd is reverse automatic differentiation system. Conceptually, autograd records a graph recording all of the operations that created the data as you execute operations, giving you a directed acyclic graph whose leaves are the input tensors and roots are the output tensors. By tracing this graph from roots to leaves, you can automatically compute the gradients using the chain rule.

Internally, autograd represnts this graph as a graph of `Function` objects (really expressions), really can be `apply()`ed to compute the result of evaluating the graph. When computing the forward pass, autograd simultaneously performs the requested computations and builds up a graph representing the function that computes the gradient (the `.grad_fn` attribute of each `torch.Tensor` is an entry point into this graph). When the forward pass is completed, we evalute this graph in the
backwards pass to compute the gradients.

An important thing to note is that the graph is recreated from scrath at every iteration, and this is exactly what allows for using arbitrary Python control flow statements, that can change the overall shape and size of the graph at every iteration. You don't have to encode all possible paths before you launch th trailing - what you run is what you differentiate.


## In-place operations with autograd

## In-place correctness checks

Every tensor keeps a version counter, that is incremented every time it is marked dirty in any operation. When a Function saves any tensor for backward pass, a version counter of their containing Tensor is saved a s well. Once you access `self.saved_tensors` it is checked, and if it is greater than the saved value an error is raised. This ensures that if you're using in-place functions and not seeing any errors, you can be sure that the computed gradients are correct.














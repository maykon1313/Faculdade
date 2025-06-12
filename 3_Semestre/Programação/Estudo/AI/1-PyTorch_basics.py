# All test were made using only the CPU

import torch

#x = torch.empty(3, 3, 3)
#x = torch.rand(3, 3, 3)
#x = torch.zeros(3, 3, 3)
#x = torch.ones(3, 3, 3)

#print(x)

###################################################

#x = torch.ones(3, 3, dtype=torch.int)
#x = torch.ones(3, 3, dtype=torch.double)
#x = torch.ones(3, 3, dtype=torch.float16)

#print(x)
#print(x.dtype)
#print(x.size())

###################################################

#x = torch.tensor([12.2, 13.5])

#print(x)
#print(x.dtype)
#print(x.size())

###################################################

#x = torch.rand(2, 2, dtype = torch.double)
#y = torch.rand(2, 2, dtype = torch.double)

#print(x)
#print(y)

#z = x + y
#z = torch.add(x, y)
#x.add_(y)

#z = x - y
#z = torch.sub(x, y)
#x.sub_(y)

#z = x * y
#z = torch.mul(x, y)
#x.mul_(y)

#z = x / y
#z = torch.div(x, y)
#x.div_(y)

#print(z)
#print(x)

###################################################

#x = torch.rand(5, 3)

#print(x)
#print(x[0, :])
#print(x[:, 0])
#print(x[1, 1].item())

###################################################

#x = torch.rand(4, 4)

#y = x.view(2, 8)
#y = x.view(-1, 8)
#y = x.view(-1, 2)

#print(x)
#print(y)
#print(y.size())

###################################################

import numpy as np

#a = torch.ones(5, dtype= torch.int)
#b = a.numpy()

#a = np.ones(5)
#b = torch.from_numpy(a)

#print(a)
#print(b)

#a.add_(1)
#a += 1

# They have the same location in the memory 
#print(a)
#print(b)

#a = torch.ones(5, dtype= torch.int)
#b = a.numpy().copy()

#a = np.ones(5)
#b = torch.from_numpy(a.copy())

#print(a)
#print(b)

#a.add_(1)
#a += 1

# They don't have the same location in the memory 
#print(a)
#print(b)

###################################################

# Example for the GPU:

#if torch.cuda.is_available():
    #device = torch.device("cuda")

    #x = torch.ones(5, device = device)
    #y = torch.ones(5)

    #y = y.to(device)

    #z = x * y

    #print(z)
    ##tensor([1., 1., 1., 1., 1.], device='cuda:0')

    #z = z.to("cpu") 
    
    #print(z)
    ##tensor([1., 1., 1., 1., 1.])

    ## CPU only: 
    #print(z.pin_memory())

#else:
    #print("CUDA is not available. Running on CPU only.")

###################################################

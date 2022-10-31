# Topology-aware method to segment 3D plant tissues images.

Official github repo. for NeurIPS 2022 workshop (AI4science)

Authors: Minh Ôn Vũ Ngọc et al.

## Abstract

The study of genetic and molecular mechanisms underlying tissue morphogenesis has received a lot of attention in biology. Especially, accurate segmentation of tissues into individual cells plays an important role for quantitative analyzing the development of the growing organs. However, instance cell segmentation is still a challenging task due to the quality of the image and the fine-scale structure. Any small leakage in the boundary prediction can merge different cells together, thereby damaging the global structure of the image. In this paper, we propose an end-to-end topology-aware 3D segmentation method for plant tissues. The strength of the method is that it takes care of the 3D topology of segmented structures. Our method relies on a common deep neural network. The keystone is a training phase and a new topology-aware loss - the CavityLoss - that are able to help the network to focus on the topological errors to fix them during the learning phase. The evaluation of our method on both fixed and live plant organ datasets shows that our method outperforms state-of-the-art methods (and contrary to state-of-the-art methods, does not require any post-processing stage). The code of CavityLoss is freely available at https://github.com/onvungocminh/CavityLoss.

## Our Proposed pipeline

![Results](./images/pipeline.pdf)
![Results](./images/critical.png)

## Visualize results

![Results](./images/3Dimage.png)

## How to use this loss

Compile the loss:
```bash
python setup.py build
python setup.py install
```




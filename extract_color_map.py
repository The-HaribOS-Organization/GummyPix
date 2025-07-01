import matplotlib.pyplot as plt

colormaps = plt.colormaps()

for name in colormaps:
    cmap = plt.get_cmap(name, 256)
    data = cmap(np.linspace(0, 1, 256))[:, :3].astype(np.float32)

    data.tofile(f"color_maps/{name}.gummycm")
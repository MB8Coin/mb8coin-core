from distutils.core import setup
setup(name='MB8spendfrom',
      version='1.0',
      description='Command-line utility for mb8coin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@mb8coinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )

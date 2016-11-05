from distutils.core import setup
setup(name='PEPEspendfrom',
      version='1.0',
      description='Command-line utility for dankcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@dankcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )

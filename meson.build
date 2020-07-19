# C examples Meson Build File

project('ring_buf', 'c')

executable('ring_buf',
	[
		'test/ring_buf_test.c',
		'src/ring_buf.c',
		'src/ring_buf.h'
	],
	include_directories: include_directories('test','src'),
)

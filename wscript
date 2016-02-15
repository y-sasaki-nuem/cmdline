# vim: set ft=python ts=4 sw=4 et :
# coding: utf-8


def options(opt):
    opt.load('compiler_cxx waf_unit_test')


def configure(conf):
    conf.env.MSVC_LAZY_AUTODETECT = True
    conf.load('compiler_cxx waf_unit_test')

    if conf.env.CXX_NAME in ('gcc', 'clang'):
        conf.env.append_unique('CXXFLAGS', ['-Wall', '-std=c++11'])

    elif conf.env.CXX_NAME == 'msvc':
        conf.env.append_unique('CXXFLAGS', ['/EHsc'])


def build(bld):
    bld(source = 'test.cpp', target = 'test',
        features = 'cxx cxxprogram test')

    bld(source = 'test2.cpp', target = 'test2',
        features = 'cxx cxxprogram test')

    bld(source = 'test_any.cpp', target = 'test_any',
        features = 'cxx cxxprogram test')

    from waflib.Tools import waf_unit_test
    bld.add_post_fun(waf_unit_test.summary)
    bld.add_post_fun(waf_unit_test.set_exit_code)

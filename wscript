# vim: set ft=python ts=4 sw=4 et :
# coding: utf-8

import sys
import subprocess


def options(opt):
    opt.load('compiler_cxx waf_unit_test')


def configure(conf):
    conf.load('compiler_cxx waf_unit_test')

    # compilation flags for MSVC
    if conf.env.CXX_NAME == 'msvc':
        conf.env.append_unique('CXXFLAGS', ['/EHsc'])

    # compilation flags for g++/clang++
    elif conf.env.CXX_NAME in ('gcc', 'clang'):
        conf.env.append_unique('CXXFLAGS', ['-Wall', '-std=c++11'])

        # for Android
        if sys.platform.lower() == 'linux' and \
           str(subprocess.check_output('uname -o'.split())[:-1], encoding='utf-8').lower() == 'android':
            conf.env.append_unique('CXXFLAGS', ['-frtti', '-fexceptions'])
            conf.env.append_unique('LDFLAGS', ['-lgnustl_shared'])


def build(bld):
    bld(source = 'test.cpp', target = 'test',
        features = 'cxx cxxprogram test')

    bld(source = 'test2.cpp', target = 'test2',
        features = 'cxx cxxprogram test')

    bld(source = 'test_any.cpp', target = 'test_any',
        features = 'cxx cxxprogram test')

    import waflib.Tools.waf_unit_test as ut
    bld.add_post_fun(ut.summary)
    bld.add_post_fun(ut.set_exit_code)

import libtbx.load_env
Import("env_base","env_etc")

env_etc.annlib_dist = libtbx.env.dist_path("annlib")
env_etc.annlib_include = [env_etc.norm_join(env_etc.annlib_dist,"src"),
                          env_etc.norm_join(env_etc.annlib_dist,"include")]
env_etc.annlib_adaptbx_dist = libtbx.env.dist_path("annlib_adaptbx")
env_etc.annlib_adaptbx_include = env_etc.norm_join(
                  env_etc.annlib_adaptbx_dist,"include")

env_etc.annlib_common_includes = [
  env_etc.libtbx_include,
  env_etc.scitbx_include,
  env_etc.boost_include,
  env_etc.annlib_dist,    # for the adaptor cpp files
  env_etc.annlib_include[0],
  env_etc.annlib_include[1],
  env_etc.annlib_adaptbx_include,
]

env_etc.annlib_defines = []
myccflags_base = env_etc.ccflags_base[:]
myccflags_base.extend(env_etc.annlib_defines)
mycxxflags_base = env_etc.cxxflags_base[:]
mycxxflags_base.extend(env_etc.annlib_defines)

env = env_base.Copy(
  CCFLAGS=myccflags_base,
  CXXFLAGS=mycxxflags_base,
  SHCXXFLAGS=mycxxflags_base,
  SHLINKFLAGS=env_etc.shlinkflags,
)
env_etc.disable_strict_aliasing(env=env)

if (env_etc.static_libraries): builder = env.StaticLibrary
else:                          builder = env.SharedLibrary
builder(target='#lib/ann',
  source = ["../annlib/src/ANN.cpp",
            "../annlib/src/bd_fix_rad_search.cpp",
            "../annlib/src/bd_pr_search.cpp",
            "../annlib/src/bd_search.cpp",
            "../annlib/src/bd_tree.cpp",
            "../annlib/src/brute.cpp",
            "../annlib/src/kd_dump.cpp",
            "../annlib/src/kd_fix_rad_search.cpp",
            "../annlib/src/kd_pr_search.cpp",
            "../annlib/src/kd_search.cpp",
            "../annlib/src/kd_split.cpp",
            "../annlib/src/kd_tree.cpp",
            "../annlib/src/kd_util.cpp",
            "../annlib/src/perf.cpp",
            "ann/ann_adaptor.cpp"
           ],
  CPPPATH=env_etc.annlib_common_includes )

if (not env_etc.no_boost_python):
  Import("env_no_includes_boost_python_ext")

  env_annlib_boost_python_ext = env_no_includes_boost_python_ext.Copy()
  env_annlib_boost_python_ext.Replace(
    SHCXXFLAGS=mycxxflags_base,)
  env_etc.disable_strict_aliasing(env=env_annlib_boost_python_ext)

  env_etc.include_registry.append(
    env=env_annlib_boost_python_ext,
    paths=env_etc.annlib_common_includes + [env_etc.python_include])

  Export("env_annlib_boost_python_ext")

  SConscript("ann/boost_python/SConscript")

# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.5
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_docxfactory', [dirname(__file__)])
        except ImportError:
            import _docxfactory
            return _docxfactory
        if fp is not None:
            try:
                _mod = imp.load_module('_docxfactory', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _docxfactory = swig_import_helper()
    del swig_import_helper
else:
    import _docxfactory
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class WordProcessingCompiler(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, WordProcessingCompiler, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, WordProcessingCompiler, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_getmethods__["get_instance"] = lambda x: _docxfactory.WordProcessingCompiler_get_instance
    if _newclass:
        get_instance = staticmethod(_docxfactory.WordProcessingCompiler_get_instance)
    __swig_destroy__ = _docxfactory.delete_WordProcessingCompiler
    __del__ = lambda self: None

    def compile(self, p_srcFileName, p_dstFileName):
        return _docxfactory.WordProcessingCompiler_compile(self, p_srcFileName, p_dstFileName)

    def set_temp_dir(self, *args):
        return _docxfactory.WordProcessingCompiler_set_temp_dir(self, *args)

    def get_work_dir(self):
        return _docxfactory.WordProcessingCompiler_get_work_dir(self)

    def get_temp_dir(self):
        return _docxfactory.WordProcessingCompiler_get_temp_dir(self)
WordProcessingCompiler_swigregister = _docxfactory.WordProcessingCompiler_swigregister
WordProcessingCompiler_swigregister(WordProcessingCompiler)

def WordProcessingCompiler_get_instance():
    return _docxfactory.WordProcessingCompiler_get_instance()
WordProcessingCompiler_get_instance = _docxfactory.WordProcessingCompiler_get_instance

class WordProcessingMerger(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, WordProcessingMerger, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, WordProcessingMerger, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined")
    __repr__ = _swig_repr
    __swig_getmethods__["get_instance"] = lambda x: _docxfactory.WordProcessingMerger_get_instance
    if _newclass:
        get_instance = staticmethod(_docxfactory.WordProcessingMerger_get_instance)
    __swig_destroy__ = _docxfactory.delete_WordProcessingMerger
    __del__ = lambda self: None

    def load(self, p_fileName):
        return _docxfactory.WordProcessingMerger_load(self, p_fileName)

    def save(self, *args):
        return _docxfactory.WordProcessingMerger_save(self, *args)

    def print_doc(self, p_printerName, p_copyCnt=1):
        return _docxfactory.WordProcessingMerger_print_doc(self, p_printerName, p_copyCnt)

    def close(self):
        return _docxfactory.WordProcessingMerger_close(self)

    def merge(self, p_data):
        return _docxfactory.WordProcessingMerger_merge(self, p_data)

    def setChartValue(self, *args):
        return _docxfactory.WordProcessingMerger_setChartValue(self, *args)

    def setClipboardValue(self, *args):
        return _docxfactory.WordProcessingMerger_setClipboardValue(self, *args)

    def paste(self, *args):
        return _docxfactory.WordProcessingMerger_paste(self, *args)

    def set_update_toc_method(self, p_method):
        return _docxfactory.WordProcessingMerger_set_update_toc_method(self, p_method)

    def get_update_toc_method(self):
        return _docxfactory.WordProcessingMerger_get_update_toc_method(self)

    def get_fields(self):
        return _docxfactory.WordProcessingMerger_get_fields(self)

    def get_items(self):
        return _docxfactory.WordProcessingMerger_get_items(self)

    def get_item_parent(self, p_itemName):
        return _docxfactory.WordProcessingMerger_get_item_parent(self, p_itemName)

    def get_item_fields(self, p_itemName):
        return _docxfactory.WordProcessingMerger_get_item_fields(self, p_itemName)

    def set_code_page(self, *args):
        return _docxfactory.WordProcessingMerger_set_code_page(self, *args)

    def set_num_frac_sep(self, p_frac=0):
        return _docxfactory.WordProcessingMerger_set_num_frac_sep(self, p_frac)

    def set_num_th_sep(self, p_th=0):
        return _docxfactory.WordProcessingMerger_set_num_th_sep(self, p_th)

    def set_date_format(self, *args):
        return _docxfactory.WordProcessingMerger_set_date_format(self, *args)

    def set_year_offset(self, p_year=0):
        return _docxfactory.WordProcessingMerger_set_year_offset(self, p_year)

    def set_first_week_day(self, *args):
        return _docxfactory.WordProcessingMerger_set_first_week_day(self, *args)

    def set_week_day_names(self, *args):
        return _docxfactory.WordProcessingMerger_set_week_day_names(self, *args)

    def set_month_names(self, *args):
        return _docxfactory.WordProcessingMerger_set_month_names(self, *args)

    def get_code_page(self):
        return _docxfactory.WordProcessingMerger_get_code_page(self)

    def get_num_frac_sep(self):
        return _docxfactory.WordProcessingMerger_get_num_frac_sep(self)

    def get_num_th_sep(self):
        return _docxfactory.WordProcessingMerger_get_num_th_sep(self)

    def get_date_format(self):
        return _docxfactory.WordProcessingMerger_get_date_format(self)

    def get_year_offset(self):
        return _docxfactory.WordProcessingMerger_get_year_offset(self)

    def get_first_week_day(self):
        return _docxfactory.WordProcessingMerger_get_first_week_day(self)

    def get_week_day_full_names(self):
        return _docxfactory.WordProcessingMerger_get_week_day_full_names(self)

    def get_week_day_short_names(self):
        return _docxfactory.WordProcessingMerger_get_week_day_short_names(self)

    def get_month_full_names(self):
        return _docxfactory.WordProcessingMerger_get_month_full_names(self)

    def get_month_short_names(self):
        return _docxfactory.WordProcessingMerger_get_month_short_names(self)

    def set_temp_dir(self, *args):
        return _docxfactory.WordProcessingMerger_set_temp_dir(self, *args)

    def get_work_dir(self):
        return _docxfactory.WordProcessingMerger_get_work_dir(self)

    def get_temp_dir(self):
        return _docxfactory.WordProcessingMerger_get_temp_dir(self)
WordProcessingMerger_swigregister = _docxfactory.WordProcessingMerger_swigregister
WordProcessingMerger_swigregister(WordProcessingMerger)

def WordProcessingMerger_get_instance():
    return _docxfactory.WordProcessingMerger_get_instance()
WordProcessingMerger_get_instance = _docxfactory.WordProcessingMerger_get_instance

from datetime	import datetime, date
from sys		import version_info

def WordProcessingMerger_set_clipboard_value(self, item_name, field_name, val):
  if val is None: return
  if isinstance(val, datetime) or isinstance(val, date): val = str(val)
  return self.setClipboardValue(item_name, field_name, val)
WordProcessingMerger.set_clipboard_value = WordProcessingMerger_set_clipboard_value

def WordProcessingMerger_set_chart_value(self, item_name, field_name, series, category, val):
  if category is None: return
  if isinstance(category, datetime) or isinstance(category, date): val = str(category)
  return self.setChartValue(item_name, field_name, series, category, val)
WordProcessingMerger.set_chart_value = WordProcessingMerger_set_chart_value

# This file is compatible with both classic and new-style classes.



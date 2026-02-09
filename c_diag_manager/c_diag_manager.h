#ifndef CDIAG_MANAGER_H
#define CDIAG_MANAGER_H

#include <stdbool.h>

extern const int DIAG_OTHER;
extern const int DIAG_OCEAN;
extern const int DIAG_ALL;

extern void cFMS_diag_init(int *diag_model_subset, int *time_init, char *err_msg);

extern int cFMS_diag_axis_init_cfloat(char *name, int *naxis_data, float *axis_data, char *units, char *cart_name,
                                      int *domain_id, char *long_name, int *direction, char *set_name, int *edges,
                                      char *aux, char *req, int *tile_count, int *domain_position, bool *not_xy);

extern int cFMS_diag_axis_init_cdouble(char *name, int *naxis_data, double *axis_data, char *units, char *cart_name,
                                       int *domain_id, char *long_name, int *direction, char *set_name, int *edges,
                                       char *aux, char *req, int *tile_count, int *domain_position, bool *not_xy);

extern void cFMS_diag_end(int *time_end);

extern bool c_diag_manager_is_initialized();

extern void cFMS_diag_set_time_end(int* time_end, char* err_msg);

extern void cFMS_diag_send_complete(int *timestep, char *err_msg);

extern int cFMS_register_diag_field_scalar_int(char *module_name, char *field_name, char *long_name,
                                               char *units, int* time, int *missing_value, int *range,
                                               char *standard_name, bool *do_not_log, char *err_msg,
                                               int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_scalar_cfloat(char *module_name, char *field_name, char *long_name,
                                                  char *units, int* time, float *missing_value, float *range,
                                                  char *standard_name, bool *do_not_log, char *err_msg,
                                                  int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_scalar_cdouble(char *module_name, char *field_name, char *long_name,
                                                   char *units, int* time, double *missing_value, double *range,
                                                   char *standard_name, bool *do_not_log, char *err_msg,
                                                   int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_array_cint(char *module_name, char *field_name, int *axes, char *long_name,
                                               char *units, int* time, int *missing_value, int *range, bool *mask_variant,
                                               char *standard_name, bool *verbose, bool *do_not_log, char *err_msg,
                                               char *interp_method, int *tile_count, int *area, int *volume,
                                               char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_array_cfloat(char *module_name, char *field_name, int *axes, char *long_name,
                                                 char *units, int* time, float *missing_value, float *range, bool *mask_variant,
                                                 char *standard_name, bool *verbose, bool *do_not_log, char *err_msg,
                                                 char *interp_method, int *tile_count, int *area, int *volume,
                                                 char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_array_cdouble(char *module_name, char *field_name, int *axes, char *long_name,
                                                  char *units, int* time, double *missing_value, double *range, bool *mask_variant,
                                                  char *standard_name, bool *verbose, bool *do_not_log, char *err_msg,
                                                  char *interp_method, int *tile_count, int *area, int *volume,
                                                  char *realm, bool *multiple_send_data);

extern bool cFMS_diag_send_data_2d_cint(int *diag_field_id, int *field_shape, int *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_3d_cint(int *diag_field_id, int *field_shape, int *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_4d_cint(int *diag_field_id, int *field_shape, int *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_5d_cint(int *diag_field_id, int *field_shape, int *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_2d_cfloat(int *diag_field_id, int *field_shape, float *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_3d_cfloat(int *diag_field_id, int *field_shape, float *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_4d_cfloat(int *diag_field_id, int *field_shape, float *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_5d_cfloat(int *diag_field_id, int *field_shape, float *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_2d_cdouble(int *diag_field_id, int *field_shape, double *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_3d_cdouble(int *diag_field_id, int *field_shape, double *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_4d_cdouble(int *diag_field_id, int *field_shape, double *field, char *err_msg, bool *convert_cf_data, int* time);
extern bool cFMS_diag_send_data_5d_cdouble(int *diag_field_id, int *field_shape, double *field, char *err_msg, bool *convert_cf_data, int* time);

#endif

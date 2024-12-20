!***********************************************************************
!*                   GNU Lesser General Public License
!*
!* This file is part of the GFDL Flexible Modeling System (FMS).
!*
!* FMS is free software: you can redistribute it and/or modify it under
!* the terms of the GNU Lesser General Public License as published by
!* the Free Software Foundation, either version 3 of the License, or (at
!* your option) any later version.
!*
!* FMS is distributed in the hope that it will be useful, but WITHOUT
!* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
!* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
!* for more details.
!*
!* You should have received a copy of the GNU Lesser General Public
!* License along with FMS.  If not, see <http://www.gnu.org/licenses/>.
!***********************************************************************
submodule(cfms_mod) cmpp_domains_smod
  
  implicit none

contains
  
  !> cFMS_calls mpp_define_domains2D to define the domain with id=domain_id.  Domain_id must be
  !! an integer.  This wrapper assumes C indexing convention where array indexing starts from 0
  module subroutine cFMS_define_domains(global_indices, layout, domain_id, pelist, &
       xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name,              &
       symmetry, memory_size, whalo, ehalo, shalo, nhalo, is_mosaic, tile_count,   &
       tile_id, complete, x_cyclic_offset, y_cyclic_offset) bind(C, name="cFMS_define_domains")

    implicit none   
    integer, intent(in) :: global_indices(4) 
    integer, intent(in) :: layout(2)
    integer, intent(in),  optional :: domain_id
    integer, intent(in), optional :: pelist(npes) 
    integer, intent(in),  optional :: xflags, yflags
    integer, intent(in),  optional :: xhalo, yhalo
    integer, intent(in), optional :: xextent(layout(1)), yextent(layout(2))
    logical, intent(in), optional :: maskmap(layout(1),layout(2))
    character(c_char), intent(in), optional :: name(NAME_LENGTH)
    logical, intent(in),  optional :: symmetry
    integer, intent(in), optional :: memory_size(2)
    integer, intent(in),  optional :: whalo, ehalo, shalo, nhalo
    logical, intent(in),  optional :: is_mosaic
    integer, intent(in),  optional :: tile_count
    integer, intent(in),  optional :: tile_id
    logical, intent(in),  optional :: complete
    integer, intent(in),  optional :: x_cyclic_offset
    integer, intent(in),  optional :: y_cyclic_offset

    integer :: i, global_indices_f(4) , tile_id_f;
    character(len=NAME_LENGTH) :: name_f = "domain"
    
    if(present(name)) name_f = fms_string_utils_c2f_string(name)

    tile_id_f = tile_id + 1;
    global_indices_f = global_indices + 1
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_domains(global_indices_f, layout, current_domain,                         &
         pelist, xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_f, symmetry,  memory_size, &
         whalo, ehalo, shalo, nhalo, is_mosaic, tile_count, tile_id_f, complete, x_cyclic_offset, y_cyclic_offset)

  end subroutine cFMS_define_domains


  !> cFMS_define_io_domain
  module subroutine cFMS_define_io_domain(io_layout, domain_id) bind(C, name="cFMS_define_io_domain")
    
    implicit none
    integer, intent(in) :: io_layout(2)
    integer, intent(in),  optional :: domain_id
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_io_domain(current_domain, io_layout)
    
  end subroutine cFMS_define_io_domain


  !> cFMS_define_layout
  module subroutine cFMS_define_layout(global_indices, ndivs, layout) bind(C, name="cFMS_define_layout")
    
    implicit none
    integer, intent(in) :: global_indices(4)
    integer, intent(in) :: ndivs
    integer, intent(out) :: layout(2)

    call fms_mpp_domains_define_layout(global_indices, ndivs, layout)
    
  end subroutine cFMS_define_layout
  

  !> cFMS_define_nest_domain calls mpp_define_nest_domains to define the nest domain with id=nest_domain_id.
  !! Nest_domain_id must be an integer.  This wrapper assumes C indexing convention where array indexing starts from 0  
  module subroutine cFMS_define_nest_domains(num_nest, ntiles, nest_level, tile_fine, tile_coarse,               &
                                     istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile, &
                                     x_refine, y_refine, nest_domain_id, domain_id, extra_halo, name)            &
                                                                            bind(C, name="cFMS_define_nest_domains")

    implicit none
    integer, intent(in) :: num_nest
    integer, intent(in) :: ntiles
    integer, intent(in) :: nest_level(num_nest)
    integer, intent(in) :: tile_fine(num_nest)
    integer, intent(in) :: tile_coarse(num_nest)
    integer, intent(in) :: istart_coarse(num_nest)
    integer, intent(in) :: icount_coarse(num_nest)
    integer, intent(in) :: jstart_coarse(num_nest)
    integer, intent(in) :: jcount_coarse(num_nest)
    integer, intent(in) :: npes_nest_tile(ntiles)
    integer, intent(in) :: x_refine(num_nest)
    integer, intent(in) :: y_refine(num_nest)
    integer, intent(in),  optional :: nest_domain_id, domain_id
    integer, intent(in),  optional :: extra_halo
    character(c_char), intent(in), optional :: name(NAME_LENGTH)

    integer :: i, istart_coarse_f(num_nest), jstart_coarse_f(num_nest)
    integer :: tile_fine_f(num_nest), tile_coarse_f(num_nest)
    character(100) :: name_f = "nest"    

    if(present(name)) name_f = fms_string_utils_c2f_string(name)

    istart_coarse_f = istart_coarse + 1
    jstart_coarse_f = jstart_coarse + 1
    tile_fine_f = tile_fine + 1
    tile_coarse_f = tile_coarse + 1
    
    call cFMS_set_current_nest_domain(nest_domain_id)
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_nest_domains(current_nest_domain, current_domain, num_nest, nest_level, &
         tile_fine_f, tile_coarse_f, istart_coarse_f, icount_coarse, jstart_coarse_f, jcount_coarse, npes_nest_tile,&
         x_refine, y_refine, extra_halo, name_f)
    
  end subroutine cFMS_define_nest_domains


  function cFMS_domain_is_initialized(domain_id) bind(C, name="cFMS_domain_is_initialized")

    implicit none
    integer, intent(in), optional :: domain_id
    logical :: cFMS_domain_is_initialized

    call cFMS_set_current_domain(domain_id)
    cFMS_domain_is_initialized = fms_mpp_domains_domain_is_initialized(current_domain)

  end function cFMS_domain_is_initialized

  
  !> cFMS_set_current_domain sets the domain to the current_domain where the
  !! current_domain has id=domain_id
  module subroutine cFMS_set_current_domain(domain_id)

    implicit none
    integer, intent(in), optional :: domain_id
    
    if(present(domain_id)) then
       current_domain => domain(domain_id)
    else
       current_domain => domain(0)
    end if
    
  end subroutine cFMS_set_current_domain


  !> cFMS_set_current_nest_domain sets the nest_domain to the current_nest_domain
  !! where the current_nest_domain has id=nest_domain_id  
  module subroutine cFMS_set_current_nest_domain(nest_domain_id)

    implicit none
    integer, intent(in), optional :: nest_domain_id
    
    if(present(nest_domain_id)) then
       current_nest_domain => nest_domain(nest_domain_id)
    else
       current_nest_domain => nest_domain(0)
    end if
    
  end subroutine cFMS_set_current_nest_domain
  

end submodule cmpp_domains_smod

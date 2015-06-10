/**
   @file
   apply.hpp

   @brief
   UNDOCUMENTED

   @copyright	
   2015 Halliburton Energy Services, Inc.

   @author: 
   Samuel Johnson <samuel.johnson@halliburton.com>

 This is a CONFIDENTIAL document.
Neither the whole or any part of this document may
be reproduced, stored in any retrieval system or
transmitted in any form or by any means (electronic,
mechanical, reprographic, recording or otherwise)
without the prior consent of the copyright owner.
*/


#ifndef APPLY_HPP_INCLUDED_995287732558119082
#define APPLY_HPP_INCLUDED_995287732558119082

//
// ... Combine header files
//
#include <combine/idx.hpp>

namespace Combine
{

  struct Apply
  {
    template< typename F, typename Xs >
    constexpr auto 
    operator ()( F&& f, Xs&& xs )
    {
      return aux( gen_Idx< length( xs ) >(), forward<f>( f ), forwar<Xs>( xs ));
    }
  private:

    template< size_t ... indices, typename F, typename Xs >
    constexpr auto
    aux( Idx< indices
  }
  
} // end of namespace Combine


#endif // APPLY_HPP_INCLUDED_995287732558119082

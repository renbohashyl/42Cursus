/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:09:37 by jbak              #+#    #+#             */
/*   Updated: 2022/12/29 19:53:45 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool	bsp( Point const &a, Point const &b, Point const &c, Point const &point);

int	main( void )
{
	Point	a(1.0f, 1.0f);
	Point	b(10.0f, 10.f);
	Point	c(25.0f, 1.0f);
	Point	point(5.5f , 5.3f);

	std::cout << bsp(a, b, c, point) << std::endl;
}
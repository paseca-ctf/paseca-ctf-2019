use paseca;

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;


CREATE TABLE IF NOT EXISTS `img` (
  `id` int(11) NOT NULL,
  `src` varchar(255) NOT NULL,
  `allowed` tinyint(1) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `img` (`id`, `src`, `allowed`) VALUES
(16754, '0HWO22NHaIQ.jpg', 1),
(16755, '4xk9vzIazjE.jpg', 1),
(16756, 'z1PScI9U_Rw.jpg', 1),
(16757, '5Y-FfCz23_A.jpg', 1),
(16758, 'AlOSMDAPu4E.jpg', 1),
(16759, 'AxNYBhIP78g.jpg', 1),
(16760, 'EHzD1LM9Atw.jpg', 1),
(16761, 'fcz6nUcM1ns.jpg', 1),
(16762, 'fyLQ4rn7KiE.jpg', 1),
(16763, 'g4E3YKSukB4.jpg', 1),
(16764, 'Gb8OQ38fmcc.jpg', 1),
(16765, 'JVkAv4n2acw.jpg', 1),
(16766, 'ko0B3xaoTy0.jpg', 1),
(16767, 'lQrG1oCxQyI.jpg', 1),
(16768, 'lUa1uzHbp1o.jpg', 1),
(16769, 'M51Dc_5aXxU.jpg', 1),
(16770, 'mAigr1A7yJs.jpg', 1),
(16771, 'mwfFFCZCWFA.jpg', 1),
(16772, 'mXj4Ttm1-wE.jpg', 1),
(16773, 'PK6DHQaMHfg.jpg', 1),
(16774, 'qq1mD-7zhcw.jpg', 1),
(16775, 'R5EEPpciqmw.jpg', 1),
(16776, 'pyjlhjC4bBk.jpg', 0),
(16777, 'SI4sDQm-LIA.jpg', 1),
(16778, 'sMhdDXKA7KU.jpg', 1),
(16779, 'TZoWcq1oD5g.jpg', 1),
(16780, 'vppxVsdf9Fc.jpg', 1),
(16781, 'woCrWsnVet4.jpg', 1),
(16782, '5Fl4k01CXTQ.jpg', 1);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

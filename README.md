# FluorescenceLifetimeToy
A little toy to demonstrate fluorescence lifetime in time domain and frequency domain. Supports time and frequency domain fluorescence lifetime spectroscopy modes. Compared to measuring the steady state fluorescence intensity, fluorescence lifetime spectroscopy is less sensitive to ambient light, photo bleaching, and changes in the optical path. Fluorphores with overlapping emmission spectra can also be differentiated from each other if they have sufficiently dissimilar fluorescent lifetimes.  

![Image of the fluorescence lifetime demonstrator](/Images/FluorescenceLifetimeToy.png)

## Time domain fluorescence
![Graph of time domain fluorescence](/Images/TimeDomain.png)

Time domain fluorescence spectroscopy uses a pulsed excitation source to excite a fluorophore then allow it to decay once the excitation source is turned off. The fluorescent lifetime can be measured directly from the decay profile by fitting the following function:

$$ I(t) = N_0 \times e^{(-t/\tau)} $$

where $N_0$ is the intensity at $time = 0$, and $\tau$ is the fluorescence lifetime.

### Short lifetime demonstration
If the lifetime is sufficiently short compared to the pulse width, the excitation source and the fluorphore will appear to increase in intensity at the same time.

![Short lifetime demonstration](/Images/TimeDomainShortLifetime.gif)

### Medium lifetime demonstration
As the lifetime increases, the exponential increase in intensity after the light turns on and the exponential decay in intensity become visible. 

![Medium lifetime demonstration](/Images/TimeDomainMediumLifetime.gif)

### Long lifetime demonstration
If the lifetime is long enough compared to the off period of the excitation source, the fluorophore will not fully decay before the excitation source turns back on.

![Long lifetime demonstration](/Images/TimeDomainLongLifetime.gif)

## Frequency domain fluorescence
![Graph of frequency domain fluorescence](/Images/FrequencyDomain.png)

Time domain fluorescence spectroscopy uses a continuously modulated excitation source. The intensity of the fluorophore matches the frequency of the excitation source, but the phase shift between the two varies depending on the lifetime of the fluorophore. A longer lifetime results in a larger phase shift. The phase shift is given by the following function:

$$ \phi = arctan(2 \times \pi \times f \times \tau) $$

where $\phi$ is the phase shift, $f$ is the modulation frequency, and $\tau$ is the fluorescence lifetime. The change in relative amplitude (compared to steady state fluorescence) is given by:

$$ m = \frac{1}{\sqrt{1+ (2 \times \pi \times f)^2 \times \tau^2}} $$

The current version of the code does not support dynamic amplitude modulation. I might get around to adding it at some time. 

### Short lifetime demonstration
If the lifetime is sufficiently short compared to the wavelength of the excitation source, the phase shift will appear to be 0.

![Short lifetime demonstration](/Images/FrequencyDomainShortLifetime.gif)

### Medium lifetime demonstration
As the lifetime increases, the phase shift between the excitation source and the fluorophore become visible. 

![Medium lifetime demonstration](/Images/FrequencyDomainMediumLifetime.gif)
